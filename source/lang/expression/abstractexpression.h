#ifndef TEA_ABSTRACTEXPRESSION_H
#define TEA_ABSTRACTEXPRESSION_H

#include <QObject>
#include <QString>

#include "assembler/assemblervalue.h"
#include "lang/print/printhint.h"

namespace tea {

class CodeAssembler;

class AbstractExpression : public QObject {
public:
	AbstractExpression(QObject* parent = nullptr);
	virtual QString toString() const = 0;
	virtual AssemblerValue assemble(CodeAssembler* assembler) const = 0;
	virtual PrintHint printHint() const;
	virtual uint byteSize() const;
};

} // namespace tea

#endif // TEA_ABSTRACTEXPRESSION_H
