#include <QCoreApplication>
#include <QFile>

#include <QDebug>
#include <QFileInfo>

#include "lang/library/codelibrary.h"
#include "lang/valuelibrary.h"

#include "lang/lexer/lexer.h"
#include "lang/parser/parser.h"
#include "lang/assembler/codeassembler.h"

#include "lang/disassembler/codedisassembler.h"
#include "lang/print/statementprinter.h"

#include "assemblercontroller.h"

Q_DECLARE_METATYPE(tea::Token)
Q_DECLARE_METATYPE(tea::AssemblyException)
Q_DECLARE_METATYPE(tea::AssemblyLine)

int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);

	qRegisterMetaType<tea::AssemblyLine>();
	qRegisterMetaType<tea::Token>();
	qRegisterMetaType<tea::AssemblyException>();

	tea::AssemblerController controller;
	controller.start("out.tea", "FE5.debug.sfc");

	return app.exec();
}

/*
int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	Q_UNUSED(app);

	bool decompMode = true;
	QString romFile = "FE5_J_UNHEADERED.sfc";
	quint64 offset = 0x65561;
	QString decompType = "chapterEventPointers";
	QString fileName = "out.tea";

	{
		QStringList list = QCoreApplication::arguments();

		for (int i=0; i<list.size()-1; ++i) {
			if (list[i] == "disassemble")
				decompMode = true;
			else if (list[i] == "assemble")
				decompMode = false;
			else if (list[i] == "-rom")
				romFile = list[++i];
			else if (list[i] == "-offset")
				offset = list[++i].toLongLong(nullptr, 0);
			else if (list[i] == "-type")
				decompType = list[++i];
			else if (list[i] == "-file")
				fileName = list[++i];
		}
	}

	QFile file(fileName);

	tea::ROM rom;
	rom.loadFromFile(romFile);

	tea::CodeLibrary lib;
	lib.loadFromDir("./code/");

	tea::ValueLibrary valLib;
	valLib.loadFromDir("./code/");

	if (decompMode) {
		tea::CodeDisassembler disassembler(&rom, &lib, &valLib, nullptr);
		tea::DisassemblerState state;

		disassembler.disassemble(offset, decompType, state);

		if (!file.open(QIODevice::WriteOnly))
			return 1;

		QTextStream stream(&file);
		tea::StatementPrinter().printStatements(stream, disassembler.makeStatements());

		file.close();
	} else {
		if (!file.open(QIODevice::ReadOnly))
			return 1;

		QString data = file.readAll();
		file.close();

		tea::Lexer lexer;
		tea::Parser parser(&lib, &lexer);
		tea::CodeAssembler assembler(&rom, &valLib);

		QObject::connect(&lexer, &tea::Lexer::tokenReady, &parser, &tea::Parser::handleToken);
		QObject::connect(&parser, &tea::Parser::statementReady, &assembler, &tea::CodeAssembler::handleStatement);

		QObject::connect(&lexer, &tea::Lexer::error, [] (QStringRef, QString what) {
			qDebug() << what;
		});

		QObject::connect(&parser, &tea::Parser::error, [] (QString what) {
			qDebug() << what;
		});

		lexer.tokenize(data.midRef(0));

#ifdef NDEBUG
		assembler.outputToFile(romFile);
#else
		assembler.outputToFile(romFile + ".debug.sfc");
#endif
	}

	return 0;
} //*/
