#include "codeexpression.h"

namespace tea {

CodeExpression::CodeExpression(const CodeTemplate* codeTemplate, QList<AbstractExpression*> parameters, QObject* parent)
	: AbstractExpression(parent), mCodeTemplate(codeTemplate), mParameters(parameters) {}

QString CodeExpression::toString() const {
	QStringList resultList(mCodeTemplate->name());

	for (AbstractExpression* exp : mParameters)
		resultList.append(exp->toString());

	return resultList.join(" ");
}

PrintHint CodeExpression::printHint() const {
	return mCodeTemplate->printHint();
}

uint CodeExpression::byteSize() const {
	return mCodeTemplate->size();
}

} // namespace tea
