#include "labelexpression.h"

#include <QStringBuilder>

namespace tea {

LabelExpression::LabelExpression(QString labelName, QObject* parent)
	: AbstractExpression(parent), mLabelName(labelName) {}

QString LabelExpression::toString() const {
	return mLabelName % ":";
}

} // namespace tea
