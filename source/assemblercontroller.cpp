#include "assemblercontroller.h"

#include <QCoreApplication>

namespace tea {

AssemblerController::AssemblerController() {
	mLexer = new Lexer;
	mParser = new Parser;
	mAssembler = new CodeAssembler;
}

void AssemblerController::start(QString fileName) {
	// Moving Workers to their respective threads
	mPreprocessor->moveToThread(&mPreprocessorThread);
	mLexer->moveToThread(&mLexerThread);
	mParser->moveToThread(&mParserThread);
	mAssembler->moveToThread(&mAssemblerThread);

	// Setting up Assembly chain
	QObject::connect(this, &startedAssembling, mPreprocessor, &Preprocessor::handleFile);
	QObject::connect(mPreprocessor, &Preprocessor::lineReady, mLexer, &Lexer::handleLine);
	QObject::connect(mLexer, &Lexer::tokenReady, mParser, &Parser::handleToken);
	QObject::connect(mParser, &Parser::statementReady, mAssembler, &CodeAssembler::handleStatement);

	// Setting up Finish chain
	QObject::connect(mPreprocessor, &Preprocessor::finished, mLexer, &Lexer::finishLexing);
	QObject::connect(mLexer, &Lexer::finished, mParser, &Parser::finishParsing);
	QObject::connect(mParser, &Parser::finished, mAssembler, &CodeAssembler::finishAssembling);
	QObject::connect(mAssembler, &CodeAssembler::finished, this, &AssemblerController::finish);

	// Setting up automatic deletion
	QObject::connect(&mPreprocessorThread, &QThread::finished, mPreprocessor, &QObject::deleteLater);
	QObject::connect(&mLexerThread, &QThread::finished, mLexer, &QObject::deleteLater);
	QObject::connect(&mParserThread, &QThread::finished, mParser, &QObject::deleteLater);
	QObject::connect(&mAssemblerThread, &QThread::finished, mAssembler, &QObject::deleteLater);

	// Starting event loops
	mPreprocessorThread.start();
	mLexerThread.start();
	mParserThread.start();
	mAssemblerThread.start();

	// Beginning assembling
	emit startedAssembling(fileName);
}

void AssemblerController::finish() {
	// Print here

	mLexerThread.quit();
	mParserThread.quit();

	qApp->quit();
}

} // namespace tea
