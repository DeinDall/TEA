#include "valueexpression.h"

namespace tea {

ValueExpression::ValueExpression(QString valueName, QObject* parent)
	: AbstractExpression(parent), mValueName(valueName) {}

QString ValueExpression::toString() const {
	return mValueName;
}

AssemblerType ValueExpression::assemble(CodeAssembler* assembler) const {
	Q_UNUSED(assembler);
	return { AssemblerType::Value, mValueName };
}

} // namespace tea
