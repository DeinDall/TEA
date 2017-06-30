#ifndef TEA_CODESTATEMENT_H
#define TEA_CODESTATEMENT_H

#include "astatement.h"

#include "lang/core/code/codetemplate.h"

namespace tea {

class CodeStatement : public AStatement {
public:
	CodeStatement(const CodeTemplate* codeTemplate, QList<AExpression*> parameters, QObject* parent);

	PrintHint printHint() const;

	QList<Token> toTokens() const;
	void compute(CodeAssembler* assembler) const;

	const CodeTemplate* codeTemplate() const;

private:
	const CodeTemplate* mCodeTemplate;
	QList<AExpression*> mParameters;
};

} // namespace tea

#endif // TEA_CODESTATEMENT_H
