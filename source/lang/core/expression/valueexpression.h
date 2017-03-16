#ifndef TEA_VALUEEXPRESSION_H
#define TEA_VALUEEXPRESSION_H

#include "abstractexpression.h"

namespace tea {

class ValueExpression : public AbstractExpression {
public:
	ValueExpression(QString valueName, QObject* parent);

	QList<Token> toTokens() const;

	bool canCompute(CodeAssembler* assembler) const;
	quint64 compute(CodeAssembler* assembler) const;

private:
	QString mValueName;
};

} // namespace tea

#endif // TEA_VALUEEXPRESSION_H
