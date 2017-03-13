#ifndef TEA_ORGEXPRESSION_H
#define TEA_ORGEXPRESSION_H

#include "abstractexpression.h"

namespace tea {

class OrgExpression : public AbstractExpression {
public:
	OrgExpression(uint offset, QObject* parent = nullptr);

	QString toString() const;
	PrintHint printHint() const;

private:
	uint mOffset;
};

} // namespace tea

#endif // TEA_ORGEXPRESSION_H
