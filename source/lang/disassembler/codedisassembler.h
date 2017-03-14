#ifndef TEA_CODEDISASSEMBLER_H
#define TEA_CODEDISASSEMBLER_H

#include "lang/codetemplatelibrary.h"
#include "lang/valuelibrary.h"

#include "lang/core/expression/abstractexpression.h"

#include <QMap>
#include <QTextStream>

namespace tea {

class CodeDisassembler : public QObject {
public:
	CodeDisassembler(const CodeTemplateLibrary* library, ValueLibrary* valLib = nullptr);

	bool disassemble(ROMRef ref, QString type);
	void printOutput(QTextStream* out);

	QList<AbstractExpression*> makeExpressions(QObject* commonParent = nullptr);

protected:
	void handleLabel(ROMRef ref, QString name);
	ROMRef handleCode(ROMRef ref, Code code);

private:
	const CodeTemplateLibrary* mLibrary;
	ValueLibrary mValueLibrary;

	QMap<uint, Code> mCodeMap;
	QMap<uint, QString> mLabelMap;
};

} // namespace tea

#endif // TEA_CODEDISASSEMBLER_H
