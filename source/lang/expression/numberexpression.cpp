#include "numberexpression.h"

#include <QStringBuilder>

namespace tea {

NumberExpression::NumberExpression(quint64 value, BaseEnum base, QObject* parent)
	: AbstractExpression(parent), mValue(value), mBase(base) {}

QString NumberExpression::toString() const {
	if (mBase == BaseHex)
		return "0x" % QString::number(mValue, 16);
	return QString::number(mValue, 10);
}

AssemblerType NumberExpression::assemble(CodeAssembler* assembler) const {
	Q_UNUSED(assembler);
	return { AssemblerType::Number, QVariant(mValue) };
}

} // namespace tea
