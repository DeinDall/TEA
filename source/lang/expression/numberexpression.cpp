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

} // namespace tea
