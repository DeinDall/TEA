#include "abstractexpression.h"

namespace tea {

AbstractExpression::AbstractExpression(QObject* parent)
	: QObject(parent) {}

uint AbstractExpression::byteSize() const {
	return 0;
}

} // namespace tea
