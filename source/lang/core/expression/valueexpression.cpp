#include "valueexpression.h"

namespace tea {

ValueExpression::ValueExpression(QString valueName, QObject* parent)
	: AExpression(parent), mValueName(valueName) {}

QList<Token> ValueExpression::toTokens() const {
	return QList<Token>({ Token { Token::Identifier, QVariant(mValueName) } });
}

bool ValueExpression::canCompute(CodeAssembler* assembler) const {
	return assembler->hasValue(mValueName);
}

quint64 ValueExpression::compute(CodeAssembler* assembler) const {
	Q_UNUSED(assembler);
	return assembler->getValue(mValueName);
}

} // namespace tea
