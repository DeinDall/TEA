#ifndef TEA_LABELSTATEMENT_H
#define TEA_LABELSTATEMENT_H

#include "astatement.h"

namespace tea {

class LabelStatement : public AStatement {
public:
	LabelStatement(QString labelName, QObject* parent);

	PrintHint printHint() const;

	QList<Token> toTokens() const;
	void compute(CodeAssembler* assembler) const;

private:
	QString mLabelName;
};

} // namespace tea

#endif // TEA_LABELSTATEMENT_H
