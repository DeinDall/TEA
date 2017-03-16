#include "codedisassembler.h"

#include <QDebug>
#include <QStringBuilder>

#include <QFile>

#include "core/rom/romutil.h"

#include "lang/core/expression/numberexpression.h"
#include "lang/core/expression/valueexpression.h"
#include "lang/core/expression/tupleexpression.h"

#include "lang/core/statement/orgstatement.h"
#include "lang/core/statement/abstractstatement.h"

namespace tea {

CodeDisassembler::CodeDisassembler(const ROM* rom, const CodeTemplateLibrary* library, ValueLibrary* valLib, QObject* parent)
	: QObject(parent), mROM(rom), mLibrary(library) {
	if (valLib)
		mValueLibrary = (*valLib);
}

bool CodeDisassembler::disassemble(uint offset, QString type, DisassemblerState& state) {
	if (mCodeMap.contains(offset))
		return false; // Already decompiled given offset

	qDebug() << ("Called disassembler at 0x" % QString::number(offset, 16) % " for type " % type);

	if (offset >= mROM->size())
		return false;

	ROMRef ref = mROM->midRef(offset);
	bool atLeastOne = false;

	while (type != "null") {
		const CodeTemplate& codeTemplate = mLibrary->findTemplate(ref, type);

		if (!codeTemplate.isValid()) {
			qDebug() << ("Couldn't disassemble " % type % " at 0x" % QString::number(offset, 16) % " (next byte: 0x" % QString::number((quint8) ref.at(0), 16) % ")");
			return false;
		}

		atLeastOne = true;

		QList<AbstractExpression*> expressions;

		for (const CodeTemplate::Parameter& parameter : codeTemplate.parameters()) {
			quint64 value = parameter.readBits(ref);

			handlePossiblePointer(state, parameter, value);

			if (parameter.isTuple) {
				QList<AbstractExpression*> tupleExpressions;

				for (int i=0; i<8; ++i)
					if (((value>>(8*i)) & 0xFF))
						for (int j=tupleExpressions.size(); j<=i; ++j)
							tupleExpressions.append(makeExpression(parameter.type, ((value>>(8*j)) & 0xFF)));

				if (tupleExpressions.isEmpty())
					tupleExpressions.append(makeExpression(parameter.type, 0));

				expressions.append(new TupleExpression(tupleExpressions, returnParent()));
			} else
				expressions.append(makeExpression(parameter.type, value));
		}

		mCodeMap.insert(ref.offset(), new CodeStatement(&codeTemplate, expressions, returnParent()));

		ref = ref.mid(codeTemplate.size());
		type = state.parseArgument(codeTemplate.nextType());
	}

	return true;
}

QList<AbstractStatement*> CodeDisassembler::makeStatements() {
	QMap<uint, QList<AbstractStatement*>> mappedResult;

	for (auto it = mLabelMap.cbegin(); it != mLabelMap.cend(); ++it)
		mappedResult[it.key()].append(it.value());

	uint nextOffset = 0;
	for (auto it = mCodeMap.cbegin(); it != mCodeMap.cend(); ++it) {
		if (nextOffset != it.key())
			mappedResult[it.key()].prepend(new OrgStatement(new NumberExpression(it.key(), returnParent()), returnParent()));
		mappedResult[it.key()].append(it.value());
		nextOffset = it.key() + it.value()->codeTemplate()->size();
	}

	QList<AbstractStatement*> result;

	for (QList<AbstractStatement*> statements : mappedResult)
		result.append(statements);

	return result;
}

void CodeDisassembler::handlePossiblePointer(DisassemblerState& state, const CodeTemplate::Parameter& paramter, quint64 value) {
	if (!snes::isLoRomPointer(value))
		return;

	const CodeParameterType& type = paramter.type;

	if (type.name() != "pointer")
		return;

	QStringList toTypes = type.parameterValues("to");

	if (toTypes.isEmpty())
		return;

	QString target = state.parseArgument(toTypes.first());
	DisassemblerState newState(state);

	for (QString arg : type.parameterValues("arg")) {
		QStringList split = arg.split('=');

		if (split.size() != 2)
			continue;

		newState.setArgument(split.at(0), split.at(1));
	}

	if (disassemble(snes::offsetFromLoRomPointer(value), target, newState))
		handleLabel(paramter.name, snes::offsetFromLoRomPointer(value));
}

void CodeDisassembler::handleLabel(QString name, uint offset) {
	static uint counter = 10;
	QString labelName(name % QString::number(counter++));

	mLabelMap.insert(offset, new LabelStatement(labelName, returnParent()));
	mValueLibrary.addValue(labelName, "pointer", snes::loRomPointerFromOffset(offset));
}

AbstractExpression* CodeDisassembler::makeExpression(CodeParameterType type, quint64 value) {
	if (const Value& libValue = mValueLibrary.findValue(type, value))
		return new ValueExpression(libValue.name(), returnParent());
	else
		return new NumberExpression(value, returnParent());
}

QObject* CodeDisassembler::returnParent() {
	return (parent() ? parent() : this);
}

} // namespace tea
