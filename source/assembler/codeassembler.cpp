#include "codeassembler.h"

#include "rom/romutil.h"

#include <QFile>

namespace tea {

CodeAssembler::CodeAssembler(const ROM* rom, ValueLibrary* valLib, QObject* parent)
	: QObject(parent), mWriter(rom) {
	if (valLib)
		mValueLibrary = ValueLibrary(*valLib);
}

void CodeAssembler::markValue(uint offset, uint size, QString valueName) {
	mMarkedValues[offset] = { size, valueName };
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

void CodeAssembler::writeToFile(QString fileName) {
	for (auto it = mMarkedValues.begin(); it != mMarkedValues.end(); ++it) {
		uint offset = it.key();
		MarkedValue value = it.value();

		if (const Value& libValue = mValueLibrary.findValueFor(value.name))
			mWriter.writeAt(offset, makeNumber(libValue.value(), value.size));
	}

	mWriter.outputToFile(fileName);
}

void CodeAssembler::handleExpression(AbstractExpression* exp) {
	AssemblerType value = exp->assemble(this);

	if (value.type == AssemblerType::Data)
		writeData(value.data.toByteArray());
}

} // namespace tea
