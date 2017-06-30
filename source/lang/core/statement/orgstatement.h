#ifndef TEA_ORGSTATEMENT_H
#define TEA_ORGSTATEMENT_H

#include "astatement.h"
#include "lang/core/expression/aexpression.h"

namespace tea {

class OrgStatement : public AStatement {
public:
	OrgStatement(AExpression* expression, QObject* parent);

	PrintHint printHint() const;

	QList<Token> toTokens() const;
	void compute(CodeAssembler* assembler) const;

private:
	AExpression* mExpression;
};

} // namespace tea

#endif // TEA_ORGSTATEMENT_H
