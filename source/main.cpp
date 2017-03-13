#include <QCoreApplication>
#include <QFile>

#include <QDebug>

#include "decompiler/codedisassembler.h"
#include "rom/romutil.h"

#include "codetemplatelibrary.h"
#include "valuelibrary.h"

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "assembler/codeassembler.h"

int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	Q_UNUSED(app);

	QString romFile = "FE5_J.sfc";
	quint64 offset = 0x3E8000;
	QString decompType = "eventDefinition";
	QString outFile = "out.tea";

	{
		QStringList list = QCoreApplication::arguments();

		for (int i=0; i<list.size()-1; ++i) {
			if (list[i] == "-rom")
				romFile = list[++i];
			else if (list[i] == "-offset")
				offset = list[++i].toLongLong(nullptr, 0);
			else if (list[i] == "-type")
				decompType = list[++i];
			else if (list[i] == "-out")
				outFile = list[++i];
		}
	}

	tea::ROM rom;
	rom.loadFromFile(romFile);

	tea::CodeTemplateLibrary lib;
	lib.loadFromDir("./code/");

	tea::ValueLibrary valLib;
	valLib.loadFromDir("./code/");

	QFile file(outFile);

	if (!file.open(QIODevice::ReadOnly))
		return 1;

	QString data = file.readAll();
	file.close();

	tea::Lexer lexer;
	tea::Parser parser(&lib, &lexer);
	tea::CodeAssembler assembler(&rom, &valLib);

	QObject::connect(&lexer, &tea::Lexer::tokenReady, &parser, &tea::Parser::handleToken);
	QObject::connect(&parser, &tea::Parser::expressionReady, &assembler, &tea::CodeAssembler::handleExpression);

	QObject::connect(&lexer, &tea::Lexer::tokenError, [] (QStringRef where, QString what) {
		qDebug() << what;
	});

	QObject::connect(&parser, &tea::Parser::parseError, [] (QString what) {
		qDebug() << what;
	});

	lexer.tokenize(data.midRef(0));
	assembler.writeToFile("../../out.sfc");

	return 0;
}

int not_really_main_anymore(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	Q_UNUSED(app);

	QString romFile = "FE5_J.sfc";
	quint64 offset = 0x3E8000;
	QString decompType = "eventDefinition";
	QString outFile = "out.tea";

	{
		QStringList list = QCoreApplication::arguments();

		for (int i=0; i<list.size()-1; ++i) {
			if (list[i] == "-rom")
				romFile = list[++i];
			else if (list[i] == "-offset")
				offset = list[++i].toLongLong(nullptr, 0);
			else if (list[i] == "-type")
				decompType = list[++i];
			else if (list[i] == "-out")
				outFile = list[++i];
		}
	}

	tea::ROM rom;
	rom.loadFromFile(romFile);

	tea::CodeTemplateLibrary lib;
	lib.loadFromDir("./code/");

	tea::ValueLibrary valLib;
	valLib.loadFromDir("./code/");

	tea::CodeDisassembler decompiler(&lib, &valLib);
	decompiler.decompile(rom.midRef(offset), decompType);

	// decompiler.decompile(rom.midRef(0x3E8000), "eventDefinition");
	// decompiler.decompile(rom.midRef(tea::snes::offsetFromLoRomPointer(0xfde49b)), "eventDefinition");

	/* {
		QFile file(outFile);

		if (!file.open(QIODevice::WriteOnly))
			return 1;

		QTextStream out(&file);
		decompiler.printOutput(&out);

		file.close();
	} //*/

	QString str;

	QTextStream stream(&str);
	decompiler.printOutput(&stream);

	tea::Lexer lexer;
	lexer.tokenize(str.midRef(0));

	return 0;
}
