#include "statementprinter.h"

namespace tea {

StatementPrinter::StatementPrinter() {}

void StatementPrinter::printStatements(QTextStream& output, QList<AStatement*> statements) {
	int currentScopeDepth = 0;

	for (AStatement* statement : statements) {
		PrintHint hint = statement->printHint();

		if (hint.beforeHint() == PrintHint::IgnoreScope)
			printTokens(output, statement->toTokens());
		else {
			switch (hint.beforeHint()) {
			case PrintHint::OpenScope:
				++currentScopeDepth;
				break;

			case PrintHint::CloseScope:
				currentScopeDepth = qMax(currentScopeDepth-1, 0);
				break;

			case PrintHint::ResetScope:
				output << endl;
				currentScopeDepth = 0;
				break;

			case PrintHint::Continue:
			default:
				break;
			}

			output << QString(currentScopeDepth, '\t');
			printTokens(output, statement->toTokens());
		}

		if (!statement->comment().isEmpty())
			output << " // " << statement->comment();

		switch (hint.afterHint()) {
		case PrintHint::OpenScope:
			++currentScopeDepth;
			break;

		case PrintHint::CloseScope:
			currentScopeDepth = qMax(currentScopeDepth-1, 0);
			break;

		case PrintHint::ResetScope:
			currentScopeDepth = 0;
		case PrintHint::IgnoreScope:
			output << endl;
			break;

		case PrintHint::Continue:
		default:
			break;
		}

		output << endl;
	}
}

void StatementPrinter::printTokens(QTextStream& output, QList<Token> tokens) {
	QStringList list;

	for (Token token : tokens)
		list << token.toString();

	output << list.join(' ');
}

} // namespace tea
