#ifndef TEA_ABSTRACTEXPRESSION_H
#define TEA_ABSTRACTEXPRESSION_H

#include <QObject>
#include <QString>

#include "lang/assembler/codeassembler.h"
#include "lang/core/token.h"

namespace tea {

class CodeAssembler;

class AbstractExpression : public QObject {
public:
	AbstractExpression(QObject* parent);

	virtual QList<Token> toTokens() const = 0;

	virtual bool canCompute(CodeAssembler* assembler) const = 0;
	virtual quint64 compute(CodeAssembler* assembler) const = 0;
};

} // namespace tea

#endif // TEA_ABSTRACTEXPRESSION_H
