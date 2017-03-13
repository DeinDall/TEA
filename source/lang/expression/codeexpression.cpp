#include "codeexpression.h"

#include "assembler/codeassembler.h"
#include "rom/romutil.h"

namespace tea {

CodeExpression::CodeExpression(const CodeTemplate* codeTemplate, QList<AbstractExpression*> parameters, QObject* parent)
	: AbstractExpression(parent), mCodeTemplate(codeTemplate), mParameters(parameters) {}

QString CodeExpression::toString() const {
	QStringList resultList(mCodeTemplate->name());

	for (AbstractExpression* exp : mParameters)
		resultList.append(exp->toString());

	return resultList.join(" ");
}

AssemblerType CodeExpression::assemble(CodeAssembler* assembler) const {
	auto it = mParameters.begin();
	auto componentIt = mCodeTemplate->components().begin();

	QByteArray data;
	data.fill(0x00, mCodeTemplate->size());

	while (componentIt != mCodeTemplate->components().end()) {
		uint size = (*componentIt).size();
		uint offset = (*componentIt).offset();

		if ((*componentIt).isFixed()) {
			data.replace(offset, size, makeNumber((*componentIt).fixedValue(), size));
		} else {
			if (it == mParameters.end())
				break;

			AssemblerType value = (*it)->assemble(assembler);

			if (value.type == AssemblerType::Value) {
				assembler->markValue(assembler->currentOffset() + offset, size, value.data.toString());
			} else if (value.type == AssemblerType::Number) {
				data.replace(offset, size, makeNumber(value.data.toLongLong(), size));
			}

			++it;
		}

		++componentIt;
	}

	return { AssemblerType::Data, QVariant(data) };
}

PrintHint CodeExpression::printHint() const {
	return mCodeTemplate->printHint();
}

uint CodeExpression::byteSize() const {
	return mCodeTemplate->size();
}

} // namespace tea
