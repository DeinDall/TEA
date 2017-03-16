#include "tupleexpression.h"

namespace tea {

TupleExpression::TupleExpression(QList<AbstractExpression*> parameters, QObject* parent)
	: AbstractExpression(parent), mParameters(parameters) {}

QList<Token> TupleExpression::toTokens() const {
	QList<Token> result;

	result.append({ Token::OpenSquareBracket, QVariant() });

	for (AbstractExpression* exp : mParameters) {
		result.append(exp->toTokens());
		result.append({ Token::Comma, QVariant() });
	}

	result.last().type = Token::CloseSquareBracket;
	return result;
}

bool TupleExpression::canCompute(CodeAssembler* assembler) const {
	for (AbstractExpression* exp : mParameters)
		if (!exp->canCompute(assembler))
			return false;
	return true;
}

quint64 TupleExpression::compute(CodeAssembler* assembler) const {
	quint64 result = 0;

	for (AbstractExpression* exp : mParameters)
		result = (exp->compute(assembler) & 0xFF) | (result<<8);

	return result;
}

} // namespace tea
