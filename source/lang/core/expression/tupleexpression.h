#ifndef TEA_TUPLEEXPRESSION_H
#define TEA_TUPLEEXPRESSION_H

#include "aexpression.h"

namespace tea {

class TupleExpression : public AExpression {
public:
	TupleExpression(QList<AExpression*> parameters, QObject* parent);

	QList<Token> toTokens() const;

	bool canCompute(CodeAssembler* assembler) const;
	quint64 compute(CodeAssembler* assembler) const;

private:
	QList<AExpression*> mParameters;
};

} // namespace tea

#endif // TEA_TUPLEEXPRESSION_H
