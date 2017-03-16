#include "orgstatement.h"

#include "lang/core/keywords.h"

namespace tea {

OrgStatement::OrgStatement(AbstractExpression* expression, QObject* parent)
	: AbstractStatement(parent), mExpression(expression) {}

PrintHint OrgStatement::printHint() const {
	return PrintHint(PrintHint::ResetScope, PrintHint::OpenScope);
}

QList<Token> OrgStatement::toTokens() const {
	QList<Token> result;

	result.append({ Token::Keyword, QVariant((int) KeywordOrg) });
	result.append(mExpression->toTokens());

	return result;
}

void OrgStatement::compute(CodeAssembler* assembler) const {
	if (mExpression->canCompute(assembler)) {
		assembler->setCurrentOffset(mExpression->compute(assembler));
		mExpression->deleteLater();
	}
	// TODO: else err away
}

} // namespace tea
