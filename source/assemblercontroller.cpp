#include "assemblercontroller.h"

#include <QCoreApplication>
#include <QDebug>

namespace tea {

AssemblerController::AssemblerController() {
	mROM.loadFromFile("FE5_J_UNHEADERED.sfc");

	mCodeLibrary.loadFromDir("./code/");
	mValueLibrary.loadFromDir("./code/");

	mPreprocessor = new Preprocessor;
	mLexer = new Lexer;
	mParser = new Parser(&mCodeLibrary);
	mAssembler = new CodeAssembler(&mROM, &mValueLibrary);
}

void AssemblerController::start(QString fileName, QString outputFileName) {
	mOutputFileName = outputFileName;

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

	// Setting up Error chain
	QObject::connect(mPreprocessor, &Preprocessor::error, this, &printError);
	QObject::connect(mLexer, &Lexer::error, this, &printError);
	QObject::connect(mParser, &Parser::error, this, &printError);
	QObject::connect(mAssembler, &CodeAssembler::error, this, &printError);

	// Setting up Finish chain
	QObject::connect(mPreprocessor, &Preprocessor::finished, mLexer, &Lexer::finishLexing);
	QObject::connect(mLexer, &Lexer::finished, mParser, &Parser::finishParsing);
	QObject::connect(mParser, &Parser::finished, mAssembler, &CodeAssembler::finishAssembling);
	QObject::connect(mAssembler, &CodeAssembler::finished, this, &finish);

	// Setting up automatic deletion
	QObject::connect(&mPreprocessorThread, &QThread::finished, mPreprocessor, &QObject::deleteLater);
	QObject::connect(&mLexerThread, &QThread::finished, mLexer, &QObject::deleteLater);
	QObject::connect(&mParserThread, &QThread::finished, mParser, &QObject::deleteLater);

	// Starting event loops
	mPreprocessorThread.start();
	mLexerThread.start();
	mParserThread.start();
	mAssemblerThread.start();

	// B E G I N
	emit startedAssembling(fileName);
}

void AssemblerController::finish() {
	mPreprocessorThread.quit();
	mLexerThread.quit();
	mParserThread.quit();
	mAssemblerThread.quit();

	mAssembler->writeLayer().outputToFile(mOutputFileName);
	mAssembler->deleteLater();

	qApp->quit();
}

void AssemblerController::printError(AssemblyException exception) {
	qDebug() << (exception.scope());
	qDebug() << QString(exception.what());

	mPreprocessorThread.quit();
	mLexerThread.quit();
	mParserThread.quit();
	mAssemblerThread.quit();

	qApp->quit();
}

} // namespace tea
