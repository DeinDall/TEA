#include "labelexpression.h"

#include "assembler/codeassembler.h"
#include "rom/romutil.h"

#include <QStringBuilder>

namespace tea {

LabelExpression::LabelExpression(QString labelName, QObject* parent)
	: AbstractExpression(parent), mLabelName(labelName) {}

QString LabelExpression::toString() const {
	return mLabelName % ":";
}

AssemblerType LabelExpression::assemble(CodeAssembler* assembler) const {
	assembler->defineValue(mLabelName, snes::loRomPointerFromOffset(assembler->currentOffset()));
	return { AssemblerType::NullType, QVariant() };
}

PrintHint LabelExpression::printHint() const {
	return PrintHint(PrintHint::ResetScope, PrintHint::OpenScope);
}

} // namespace tea
