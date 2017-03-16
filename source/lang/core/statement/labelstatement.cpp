#include "labelstatement.h"

#include "core/rom/romutil.h"

namespace tea {

LabelStatement::LabelStatement(QString labelName, QObject* parent)
	: AbstractStatement(parent), mLabelName(labelName) {}

PrintHint LabelStatement::printHint() const {
	return PrintHint(PrintHint::ResetScope, PrintHint::OpenScope);
}

QList<Token> LabelStatement::toTokens() const {
	QList<Token> result;

	result.append({ Token::Identifier, QVariant(mLabelName) });
	result.append({ Token::Colon, QVariant() });

	return result;
}

void LabelStatement::compute(CodeAssembler* assembler) const {
	assembler->defineValue(mLabelName, snes::loRomPointerFromOffset(assembler->currentOffset()));
}

} // namespace tea
