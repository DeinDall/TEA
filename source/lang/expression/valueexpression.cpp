#include "valueexpression.h"

namespace tea {

ValueExpression::ValueExpression(QString valueName, QObject* parent)
	: AbstractExpression(parent), mValueName(valueName) {}

QString ValueExpression::toString() const {
	return mValueName;
}

} // namespace tea
