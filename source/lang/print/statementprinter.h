#ifndef TEA_STATEMENTPRINTER_H
#define TEA_STATEMENTPRINTER_H

#include "lang/core/statement/abstractstatement.h"

#include <QTextStream>

namespace tea {

class StatementPrinter {
public:
	StatementPrinter();

	void printStatements(QTextStream& output, QList<AbstractStatement*> statements);
	void printTokens(QTextStream& output, QList<Token> tokens);
};

} // namespace tea

#endif // TEA_STATEMENTPRINTER_H
