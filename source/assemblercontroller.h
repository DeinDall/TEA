#ifndef TEA_ASSEMBLERCONTROLLER_H
#define TEA_ASSEMBLERCONTROLLER_H

#include <QThread>

#include "lang/preprocessor/preprocessor.h"
#include "lang/lexer/lexer.h"
#include "lang/parser/parser.h"
#include "lang/assembler/codeassembler.h"

#include "lang/error/assemblyexception.h"

namespace tea {

class AssemblerController : public QObject {
	Q_OBJECT
public:
	AssemblerController();

	void start(QString fileName, QString outputFileName);

signals:
	void startedAssembling(QString inputFile);

public slots:
	void finish();
	void printError(AssemblyException exception);

private:
	QString mOutputFileName;

	QThread mPreprocessorThread;
	QThread mLexerThread;
	QThread mParserThread;
	QThread mAssemblerThread;

	ROM mROM;

	CodeLibrary mCodeLibrary;
	ValueLibrary mValueLibrary;

	Preprocessor* mPreprocessor;
	Lexer* mLexer;
	Parser* mParser;
	CodeAssembler* mAssembler;
};

} // namespace tea

#endif // TEA_ASSEMBLERCONTROLLER_H
