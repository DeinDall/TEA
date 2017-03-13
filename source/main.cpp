#include <QCoreApplication>
#include <QFile>

#include "decompiler/codedisassembler.h"
#include "rom/romutil.h"

#include "codetemplatelibrary.h"
#include "valuelibrary.h"

int main(int argc, char** argv) {
	QCoreApplication(argc, argv);

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

	{
		QFile file(outFile);

		if (!file.open(QIODevice::WriteOnly))
			return 1;

		QTextStream out(&file);
		decompiler.printOutput(&out);

		file.close();
	}

	return 0;
}
