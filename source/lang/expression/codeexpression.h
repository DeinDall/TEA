#ifndef TEA_CODEEXPRESSION_H
#define TEA_CODEEXPRESSION_H

#include "abstractexpression.h"

#include "template/codetemplate.h"

namespace tea {

class CodeExpression : public AbstractExpression {
public:
	CodeExpression(const CodeTemplate* codeTemplate, QList<AbstractExpression*> parameters, QObject* parent = nullptr);

	QString toString() const;
	AssemblerValue assemble(CodeAssembler* assembler) const;
	PrintHint printHint() const;
	uint byteSize() const;

private:
	const CodeTemplate* mCodeTemplate;
	QList<AbstractExpression*> mParameters;
};

} // namespace tea

#endif // TEA_CODEEXPRESSION_H
