#ifndef TEA_ASTATEMENT_H
#define TEA_ASTATEMENT_H

#include <QObject>
#include <QList>

#include "lang/assembler/codeassembler.h"
#include "lang/print/printhint.h"
#include "lang/core/token.h"

namespace tea {

class AStatement : public QObject {
public:
	inline AStatement(QObject* parent)
		: QObject(parent) {}

	virtual PrintHint printHint() const = 0;

	virtual QList<Token> toTokens() const = 0;
	virtual void compute(CodeAssembler* assembler) const = 0;

	inline QString comment() const { return mComment; }
	inline void setComment(QString str) { mComment = str; }

private:
	QString mComment;
};

} // namespace tea

#endif // TEA_ASTATEMENT_H
