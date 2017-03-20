#ifndef TEA_ASSEMBLERCONTROLLER_H
#define TEA_ASSEMBLERCONTROLLER_H

#include <QThread>

#include "lang/preprocessor/preprocessor.h"
#include "lang/lexer/lexer.h"
#include "lang/parser/parser.h"
#include "lang/assembler/codeassembler.h"

namespace tea {

class AssemblerController : public QObject {
	Q_OBJECT
public:
	AssemblerController();

	void start(QString fileName);

signals:
	void startedAssembling(QString inputFile);

public slots:
	void finish();

private:
	QThread mPreprocessorThread;
	QThread mLexerThread;
	QThread mParserThread;
	QThread mAssemblerThread;

	Preprocessor* mPreprocessor;
	Lexer* mLexer;
	Parser* mParser;
	CodeAssembler* mAssembler;
};

} // namespace tea

#endif // TEA_ASSEMBLERCONTROLLER_H
