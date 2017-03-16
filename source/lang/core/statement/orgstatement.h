#ifndef TEA_ORGSTATEMENT_H
#define TEA_ORGSTATEMENT_H

#include "abstractstatement.h"
#include "lang/core/expression/abstractexpression.h"

namespace tea {

class OrgStatement : public AbstractStatement {
public:
	OrgStatement(AbstractExpression* expression, QObject* parent);

	PrintHint printHint() const;

	QList<Token> toTokens() const;
	void compute(CodeAssembler* assembler) const;

private:
	AbstractExpression* mExpression;
};

} // namespace tea

#endif // TEA_ORGSTATEMENT_H
