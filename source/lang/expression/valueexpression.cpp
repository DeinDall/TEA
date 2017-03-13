#include "valueexpression.h"

namespace tea {

ValueExpression::ValueExpression(QString valueName, QObject* parent)
	: AbstractExpression(parent), mValueName(valueName) {}

QString ValueExpression::toString() const {
	return mValueName;
}

AssemblerValue ValueExpression::assemble(CodeAssembler* assembler) const {
	Q_UNUSED(assembler);
	return { AssemblerValue::Value, mValueName };
}

} // namespace tea
