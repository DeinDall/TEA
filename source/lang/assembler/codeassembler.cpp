#include "codeassembler.h"

#include "core/rom/romutil.h"

#include "lang/core/expression/abstractexpression.h"
#include "lang/core/statement/abstractstatement.h"

#include <QFile>

namespace tea {

CodeAssembler::CodeAssembler(const ROM* rom, ValueLibrary* valLib, QObject* parent)
	: QObject(parent), mWriter(rom) {
	if (valLib)
		mValueLibrary = ValueLibrary(*valLib);
}

void CodeAssembler::markExpressionUsage(uint offset, uint size, AbstractExpression* expression) {
	mMarkedExpression[offset] = { size, expression };
}

void CodeAssembler::writeData(const QByteArray data) {
	mWriter.writeAt(mCurrentOffset, data);
	mCurrentOffset += data.size();
}

void CodeAssembler::setCurrentOffset(uint offset) {
	mCurrentOffset = offset;
}

uint CodeAssembler::currentOffset() const {
	return mCurrentOffset;
}

void CodeAssembler::defineValue(QString name, quint64 value) {
	mValueLibrary.addValue(name, "any", value);
}

bool CodeAssembler::hasValue(QString name) const {
	if (mValueLibrary.findValue(name))
		return true;
	return false;
}

quint64 CodeAssembler::getValue(QString name) const {
	if (const Value& value = mValueLibrary.findValue(name))
		return value.value();
	return 0;
}

void CodeAssembler::outputToFile(QString fileName) {
	for (auto it = mMarkedExpression.begin(); it != mMarkedExpression.end(); ++it) {
		uint offset = it.key();
		MarkedExpression value = it.value();

		if (!value.expression->canCompute(this))
			break; // TODO: err away

		mWriter.writeAt(offset, makeNumber(value.expression->compute(this), value.size));
	}

	mWriter.outputToFile(fileName);
}

void CodeAssembler::handleStatement(AbstractStatement* statement) {
	statement->compute(this);
	statement->deleteLater();
}

} // namespace tea
