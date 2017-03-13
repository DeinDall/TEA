#include "orgexpression.h"

#include <QStringBuilder>

#include "assembler/codeassembler.h"

namespace tea {

OrgExpression::OrgExpression(uint offset, QObject* parent)
	: AbstractExpression(parent), mOffset(offset) {}

QString OrgExpression::toString() const {
	return "org 0x" % QString::number(mOffset, 16);
}

AssemblerValue OrgExpression::assemble(CodeAssembler* assembler) const {
	assembler->setCurrentOffset(mOffset);
	return { AssemblerValue::NullType, QVariant() };
}

PrintHint OrgExpression::printHint() const {
	return PrintHint(PrintHint::ResetScope, PrintHint::OpenScope);
}

} // namespace tea
