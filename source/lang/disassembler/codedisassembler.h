#ifndef TEA_CODEDISASSEMBLER_H
#define TEA_CODEDISASSEMBLER_H

#include "disassemblerstate.h"

#include "lang/library/codelibrary.h"
#include "lang/valuelibrary.h"

#include "lang/core/expression/abstractexpression.h"

#include "lang/core/statement/codestatement.h"
#include "lang/core/statement/labelstatement.h"

#include <QMap>
#include <QTextStream>

namespace tea {

class CodeDisassembler : public QObject {
public:
	CodeDisassembler(const ROM* rom, const CodeLibrary* library, ValueLibrary* valLib, QObject* parent);

	bool disassemble(uint offset, QString type, DisassemblerState& state);
	QList<AbstractStatement*> makeStatements();

protected:
	void handlePossiblePointer(DisassemblerState& state, const CodeTemplate::Parameter& paramter, quint64 value);
	void handleLabel(QString name, uint offset);

	AbstractExpression* makeExpression(CodeParameterType type, quint64 value);

	QObject* returnParent();

private:
	const ROM* mROM;

	const CodeLibrary* mLibrary;
	ValueLibrary mValueLibrary;

	QMap<uint, CodeStatement*> mCodeMap;
	QMap<uint, LabelStatement*> mLabelMap;
};

} // namespace tea

#endif // TEA_CODEDISASSEMBLER_H
