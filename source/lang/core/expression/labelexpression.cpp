#include "labelexpression.h"

#include "core/rom/romutil.h"
#include "lang/assembler/codeassembler.h"

#include <QStringBuilder>

namespace tea {

LabelExpression::LabelExpression(QString labelName, QObject* parent)
	: AbstractExpression(parent), mLabelName(labelName) {}

QString LabelExpression::toString() const {
	return mLabelName % ":";
}

AssemblerValue LabelExpression::assemble(CodeAssembler* assembler) const {
	assembler->defineValue(mLabelName, snes::loRomPointerFromOffset(assembler->currentOffset()));
	return { AssemblerValue::NullType, QVariant() };
}

PrintHint LabelExpression::printHint() const {
	return PrintHint(PrintHint::ResetScope, PrintHint::OpenScope);
}

} // namespace tea
