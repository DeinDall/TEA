#ifndef TEA_ABSTRACTSTATEMENT_H
#define TEA_ABSTRACTSTATEMENT_H

#include <QObject>
#include <QList>

#include "lang/assembler/codeassembler.h"
#include "lang/print/printhint.h"
#include "lang/core/token.h"

namespace tea {

class AbstractStatement : public QObject {
public:
	AbstractStatement(QObject* parent);

	virtual PrintHint printHint() const = 0;

	virtual QList<Token> toTokens() const = 0;
	virtual void compute(CodeAssembler* assembler) const = 0;
};

} // namespace tea

#endif // TEA_ABSTRACTSTATEMENT_H
