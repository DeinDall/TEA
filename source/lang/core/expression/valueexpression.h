#ifndef TEA_VALUEEXPRESSION_H
#define TEA_VALUEEXPRESSION_H

#include "aexpression.h"

namespace tea {

class ValueExpression : public AExpression {
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
