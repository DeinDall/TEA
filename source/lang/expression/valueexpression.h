#ifndef TEA_VALUEEXPRESSION_H
#define TEA_VALUEEXPRESSION_H

#include "abstractexpression.h"

namespace tea {

class ValueExpression : public AbstractExpression {
public:
	ValueExpression(QString valueName, QObject* parent = nullptr);

	QString toString() const;
	AssemblerValue assemble(CodeAssembler* assembler) const;

private:
	QString mValueName;
};

} // namespace tea

#endif // TEA_VALUEEXPRESSION_H
