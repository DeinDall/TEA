#ifndef TEA_ABSTRACTEXPRESSION_H
#define TEA_ABSTRACTEXPRESSION_H

#include <QObject>
#include <QString>

#include "lang/print/printhint.h"

namespace tea {

class AbstractExpression : public QObject {
public:
	AbstractExpression(QObject* parent = nullptr);
	virtual QString toString() const = 0;
	virtual PrintHint printHint() const;
	virtual uint byteSize() const;
};

} // namespace tea

#endif // TEA_ABSTRACTEXPRESSION_H
