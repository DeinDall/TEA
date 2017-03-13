#include "codedisassembler.h"

#include <QDebug>
#include <QStringBuilder>

#include <QFile>

#include "lang/expression/labelexpression.h"
#include "lang/expression/codeexpression.h"
#include "lang/expression/numberexpression.h"
#include "lang/expression/valueexpression.h"
#include "lang/expression/orgexpression.h"

#include "rom/romutil.h"

namespace tea {

CodeDisassembler::CodeDisassembler(const CodeTemplateLibrary* library, ValueLibrary* valLib)
	: mLibrary(library) {
	if (valLib)
		mValueLibrary = (*valLib);
}

bool CodeDisassembler::decompile(ROMRef ref, QString type) {
	if (mCodeMap.contains(ref.offset()))
		return false; // Already decompiled given offset

	// TODO: Proper logger
	// QTextStream stdstream(stdout);

	qDebug() << ("Called disassembler at 0x" % QString::number(ref.offset(), 16) % " for type " % type) << endl;

	if (ref.offset() >= ref.romPtr()->size())
		return false;

	while (type != "null") {
		const CodeTemplate& codeTemplate = mLibrary->findTemplateFor(ref, type);

		if (!codeTemplate.isValid()) {
			qDebug() << ("Couldn't disassemble at 0x" % QString::number(ref.offset(), 16) % " (next byte: 0x" % QString::number((quint8) ref.at(0), 16) % ")") << endl;
			return false;
		}

		ref = handleCode(ref, codeTemplate.makeCodeFrom(ref));
		type = codeTemplate.nextTypes().first();
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
			if (const Value& value = mValueLibrary.findValueFor(paramIt.types(), paramIt.value()))
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

ROMRef CodeDisassembler::handleCode(ROMRef ref, Code code) {
	// Cycling through parameters to handle pointers
	auto it = code.parameterIterator();
	while (it.next()) {
		if (!snes::isLoRomPointer(it.value()))
			continue;

		if (it.types().contains("pointer")) {
			QString targetType;

			for (QString type : it.types())
				if (type.startsWith("to:"))
					targetType = type.mid(3);

			if (targetType.isEmpty())
				continue;

			ROMRef offset = ref.romPtr()->midRef(snes::offsetFromLoRomPointer(it.value()));

			// Decompiling
			if (decompile(offset, targetType))
				handleLabel(offset, it.name());
		}
	}

	mCodeMap.insert(ref.offset(), code);
	return ref.mid(code.size());
}

} // namespace tea
