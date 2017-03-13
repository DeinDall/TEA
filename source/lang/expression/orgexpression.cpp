#include "orgexpression.h"

#include <QStringBuilder>

namespace tea {

OrgExpression::OrgExpression(uint offset, QObject* parent)
	: AbstractExpression(parent), mOffset(offset) {}

QString OrgExpression::toString() const {
	return "org 0x" % QString::number(mOffset, 16);
}

PrintHint OrgExpression::printHint() const {
	return PrintHint(PrintHint::ResetScope, PrintHint::OpenScope);
}

} // namespace tea
