#ifndef TEA_CODEDISASSEMBLER_H
#define TEA_CODEDISASSEMBLER_H

#include "disassemblerstate.h"

#include "lang/codetemplatelibrary.h"
#include "lang/valuelibrary.h"

#include "lang/core/expression/aexpression.h"

#include "lang/core/statement/codestatement.h"
#include "lang/core/statement/labelstatement.h"

#include <QMap>
#include <QTextStream>

namespace tea {

class CodeDisassembler : public QObject {
public:
	CodeDisassembler(const ROM* rom, const CodeTemplateLibrary* library, ValueLibrary* valLib, QObject* parent);

	inline void setPrintOffsets(bool doINow) { mPrintOffsets = doINow; }

	bool disassemble(uint offset, QString type, DisassemblerState& state);
	QList<AStatement*> makeStatements();

protected:
	void handlePossiblePointer(DisassemblerState& state, const CodeTemplate::Parameter& paramter, uint currentOffset, quint64 value);
	void handleLabel(QString name, uint offset);

	AExpression* makeExpression(CodeParameterType type, quint64 value);

	QObject* returnParent();

private:
	const ROM* mROM;

	const CodeTemplateLibrary* mLibrary;
	ValueLibrary mValueLibrary;

	QMap<uint, CodeStatement*> mCodeMap;
	QMap<uint, LabelStatement*> mLabelMap;

	bool mPrintOffsets;
};

} // namespace tea

#endif // TEA_CODEDISASSEMBLER_H
