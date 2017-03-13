#ifndef TEA_LABELEXPRESSION_H
#define TEA_LABELEXPRESSION_H

#include "abstractexpression.h"

#include <QString>

namespace tea {

class LabelExpression : public AbstractExpression {
public:
	LabelExpression(QString labelName, QObject* parent = nullptr);

	QString toString() const;
	PrintHint printHint() const;

private:
	QString mLabelName;
};

} // namespace tea

#endif // TEA_LABELEXPRESSION_H
