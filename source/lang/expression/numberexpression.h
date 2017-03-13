#ifndef TEA_NUMBEREXPRESSION_H
#define TEA_NUMBEREXPRESSION_H

#include "abstractexpression.h"

namespace tea {

class NumberExpression : public AbstractExpression {
public:
	enum BaseEnum {
		BaseDec = 10,
		BaseHex = 16
	};

public:
	NumberExpression(quint64 value, BaseEnum base, QObject* parent = nullptr);

	QString toString() const;

private:
	quint64 mValue;
	BaseEnum mBase;
};

} // namespace tea

#endif // TEA_NUMBEREXPRESSION_H
