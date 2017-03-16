#ifndef TEA_NUMBEREXPRESSION_H
#define TEA_NUMBEREXPRESSION_H

#include "abstractexpression.h"

namespace tea {

class NumberExpression : public AbstractExpression {
public:
	NumberExpression(quint64 value, QObject* parent);

	QList<Token> toTokens() const;

	bool canCompute(CodeAssembler* assembler) const;
	quint64 compute(CodeAssembler* assembler) const;

private:
	quint64 mValue;
};

} // namespace tea

#endif // TEA_NUMBEREXPRESSION_H
