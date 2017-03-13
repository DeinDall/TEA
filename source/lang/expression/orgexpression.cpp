#include "orgexpression.h"

#include <QStringBuilder>

#include "assembler/codeassembler.h"

namespace tea {

OrgExpression::OrgExpression(uint offset, QObject* parent)
	: AbstractExpression(parent), mOffset(offset) {}

QString OrgExpression::toString() const {
	return "org 0x" % QString::number(mOffset, 16);
}

AssemblerType OrgExpression::assemble(CodeAssembler* assembler) const {
	assembler->setCurrentOffset(mOffset);
	return { AssemblerType::NullType, QVariant() };
}

PrintHint OrgExpression::printHint() const {
	return PrintHint(PrintHint::ResetScope, PrintHint::OpenScope);
}

} // namespace tea
