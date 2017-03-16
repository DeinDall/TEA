#ifndef TEA_TUPLEEXPRESSION_H
#define TEA_TUPLEEXPRESSION_H

#include "abstractexpression.h"

namespace tea {

class TupleExpression : public AbstractExpression {
public:
	TupleExpression(QList<AbstractExpression*> parameters, QObject* parent);

	QList<Token> toTokens() const;

	bool canCompute(CodeAssembler* assembler) const;
	quint64 compute(CodeAssembler* assembler) const;

private:
	QList<AbstractExpression*> mParameters;
};

} // namespace tea

#endif // TEA_TUPLEEXPRESSION_H
