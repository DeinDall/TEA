#include "abstractexpression.h"

namespace tea {

AbstractExpression::AbstractExpression(QObject* parent)
	: QObject(parent) {}

PrintHint AbstractExpression::printHint() const {
	return PrintHint(PrintHint::Continue, PrintHint::Continue);
}

uint AbstractExpression::byteSize() const {
	return 0;
}

} // namespace tea
