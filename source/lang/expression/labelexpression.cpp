#include "labelexpression.h"

#include <QStringBuilder>

namespace tea {

LabelExpression::LabelExpression(QString labelName, QObject* parent)
	: AbstractExpression(parent), mLabelName(labelName) {}

QString LabelExpression::toString() const {
	return mLabelName % ":";
}

PrintHint LabelExpression::printHint() const {
	return PrintHint(PrintHint::ResetScope, PrintHint::OpenScope);
}

} // namespace tea
