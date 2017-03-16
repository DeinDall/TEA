#ifndef TEA_CODESTATEMENT_H
#define TEA_CODESTATEMENT_H

#include "abstractstatement.h"

#include "lang/core/code/codetemplate.h"

namespace tea {

class CodeStatement : public AbstractStatement {
public:
	CodeStatement(const CodeTemplate* codeTemplate, QList<AbstractExpression*> parameters, QObject* parent);

	PrintHint printHint() const;

	QList<Token> toTokens() const;
	void compute(CodeAssembler* assembler) const;

	const CodeTemplate* codeTemplate() const;

private:
	const CodeTemplate* mCodeTemplate;
	QList<AbstractExpression*> mParameters;
};

} // namespace tea

#endif // TEA_CODESTATEMENT_H
