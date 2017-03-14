#include "codedisassembler.h"

#include <QDebug>
#include <QStringBuilder>

#include <QFile>

#include "core/rom/romutil.h"

#include "lang/core/expression/labelexpression.h"
#include "lang/core/expression/codeexpression.h"
#include "lang/core/expression/numberexpression.h"
#include "lang/core/expression/valueexpression.h"
#include "lang/core/expression/orgexpression.h"

namespace tea {

CodeDisassembler::CodeDisassembler(const CodeTemplateLibrary* library, ValueLibrary* valLib)
	: mLibrary(library) {
	if (valLib)
		mValueLibrary = (*valLib);
}

bool CodeDisassembler::disassemble(ROMRef ref, QString type, DisassemblerState& state) {
	if (mCodeMap.contains(ref.offset()))
		return false; // Already decompiled given offset

	// TODO: Proper logger

	qDebug() << ("Called disassembler at 0x" % QString::number(ref.offset(), 16) % " for type " % type) << endl;

	if (ref.offset() >= ref.romPtr()->size())
		return false;

	while (type != "null") {
		const CodeTemplate& codeTemplate = mLibrary->findTemplate(ref, type);

		if (!codeTemplate.isValid()) {
			qDebug() << ("Couldn't disassemble at 0x" % QString::number(ref.offset(), 16) % " (next byte: 0x" % QString::number((quint8) ref.at(0), 16) % ")") << endl;
			return false;
		}

		ref = handleCode(ref, codeTemplate.makeCodeFrom(ref), state);
		type = state.parseArgument(codeTemplate.nextType());
	}

	return true;
}

void CodeDisassembler::printOutput(QTextStream* out) {
	int currentScopeDepth = 0;
	for (AbstractExpression* exp : makeExpressions(this)) {
		PrintHint hint(exp->printHint());

		if (hint.beforeHint() == PrintHint::IgnoreScope)
			(*out) << exp->toString() << endl;
		else {
			switch (hint.beforeHint()) {
			case PrintHint::OpenScope:
				++currentScopeDepth;
				break;

			case PrintHint::CloseScope:
				currentScopeDepth = qMax(currentScopeDepth-1, 0);
				break;

			case PrintHint::ResetScope:
				(*out) << endl;
				currentScopeDepth = 0;
				break;

			case PrintHint::Continue:
			default:
				break;
			}

			(*out) << QString(currentScopeDepth, '\t') << exp->toString() << endl;
		}

		switch (hint.afterHint()) {
		case PrintHint::OpenScope:
			++currentScopeDepth;
			break;

		case PrintHint::CloseScope:
			currentScopeDepth = qMax(currentScopeDepth-1, 0);
			break;

		case PrintHint::ResetScope:
			currentScopeDepth = 0;
		case PrintHint::IgnoreScope:
			(*out) << endl;
			break;

		case PrintHint::Continue:
		default:
			break;
		}
	}
}

QList<AbstractExpression*> CodeDisassembler::makeExpressions(QObject* commonParent) {
	QMap<uint, QList<AbstractExpression*>> mappedResult;

	for (auto it = mLabelMap.begin(); it != mLabelMap.end(); ++it)
		mappedResult[it.key()].append(new LabelExpression(it.value(), commonParent));

	for (auto it = mCodeMap.begin(); it != mCodeMap.end(); ++it) {
		const Code& code = it.value();

		QList<AbstractExpression*> parameterList;

		auto paramIt = code.parameterIterator();
		while (paramIt.next()) {
			if (const Value& value = mValueLibrary.findValue(paramIt.type(), paramIt.value()))
				parameterList.append(new ValueExpression(value.name(), commonParent));
			else
				parameterList.append(new NumberExpression(paramIt.value(), NumberExpression::BaseHex, commonParent));
		}

		mappedResult[it.key()].append(new CodeExpression(code.codeTemplate(), parameterList, commonParent));
	}

	QList<AbstractExpression*> result;

	uint nextOffset = 0;
	for (auto it = mappedResult.begin(); it != mappedResult.end(); ++it) {
		if (nextOffset != it.key()) {
			it.value().prepend(new OrgExpression(it.key(), commonParent));
			nextOffset = it.key();
		}

		for (const AbstractExpression* exp : it.value())
			nextOffset += exp->byteSize();

		result.append(it.value());
	}

	return result;
}

void CodeDisassembler::handleLabel(ROMRef ref, QString name) {
	static uint counter = 10;
	QString labelName(name % QString::number(counter++));

	mLabelMap.insert(ref.offset(), labelName);
	mValueLibrary.addValue(labelName, "pointer", snes::loRomPointerFromOffset(ref.offset()));
}

ROMRef CodeDisassembler::handleCode(ROMRef ref, Code code, DisassemblerState& state) {
	// Cycling through parameters to handle pointers
	auto it = code.parameterIterator();
	while (it.next()) {
		if (!snes::isLoRomPointer(it.value()))
			continue; // Value is not a valid pointer anyway

		const CodeParameterType& type = it.type();

		if (type.name() == "pointer") {
			QStringList toTypes = type.parameterValues("to");

			if (toTypes.isEmpty())
				continue;

			QString targetType = state.parseArgument(toTypes.first());
			DisassemblerState newState(state);

			for (QString arg : type.parameterValues("arg")) {
				QStringList split = arg.split('=');

				if (split.size() != 2)
					continue;

				newState.setArgument(split.at(0), split.at(1));
			}

			ROMRef offset = ref.romPtr()->midRef(snes::offsetFromLoRomPointer(it.value()));

			// Decompiling
			if (disassemble(offset, targetType, newState))
				handleLabel(offset, it.name());
		}
	}

	mCodeMap.insert(ref.offset(), code);
	return ref.mid(code.size());
}

} // namespace tea
