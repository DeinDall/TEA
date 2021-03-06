#include "numberexpression.h"

#include <QStringBuilder>

namespace tea {

NumberExpression::NumberExpression(quint64 value, QObject* parent)
	: AExpression(parent), mValue(value) {}

QList<Token> NumberExpression::toTokens() const {
	return QList<Token>({ Token { Token::NumberLiteral, QVariant((qint64) mValue) } });
}

bool NumberExpression::canCompute(CodeAssembler* assembler) const {
	Q_UNUSED(assembler);
	return true;
}

quint64 NumberExpression::compute(CodeAssembler* assembler) const {
	Q_UNUSED(assembler);
	return mValue;
}

} // namespace tea
