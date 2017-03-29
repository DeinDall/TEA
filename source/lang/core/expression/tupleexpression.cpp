#include "tupleexpression.h"

namespace tea {

TupleExpression::TupleExpression(QList<AbstractExpression*> parameters, QObject* parent)
	: AbstractExpression(parent), mParameters(parameters) {}

QList<Token> TupleExpression::toTokens() const {
	QList<Token> result;

	result.append(Token(Token::OpenSquareBracket, FilePosition()));

	for (AbstractExpression* exp : mParameters) {
		result.append(exp->toTokens());
		result.append(Token(Token::Comma, FilePosition()));
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

	for (int i=0; i<mParameters.size(); ++i)
		result |= ((mParameters[i]->compute(assembler) & 0xFF) << 8*i);

	return result;
}

} // namespace tea
