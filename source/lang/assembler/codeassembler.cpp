#include "codeassembler.h"

#include "core/rom/romutil.h"

#include "lang/core/expression/abstractexpression.h"
#include "lang/core/statement/abstractstatement.h"

#include <QFile>

#include <QCoreApplication>

namespace tea {

CodeAssembler::CodeAssembler(const ROM* rom, ValueLibrary* valLib, QObject* parent)
	: QObject(parent), mErrored(false), mWriter(rom) {
	if (valLib)
		mValueLibrary = ValueLibrary(*valLib);
}

void CodeAssembler::markExpressionUsage(quint64 offset, quint64 size, AbstractExpression* expression) {
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

const ROMWriteLayer& CodeAssembler::writeLayer() const {
	return mWriter;
}

void CodeAssembler::handleStatement(tea::AbstractStatement* statement) {
	if (!mErrored) {
		try {
			statement->compute(this);
		} catch (const AssemblyException& exception) {
			emit error(exception);
			mErrored = true;
		}
	}

	statement->deleteLater();
}

void CodeAssembler::finishAssembling() {
	if (!mErrored) {
		try {
			for (auto it = mMarkedExpression.begin(); it != mMarkedExpression.end(); ++it) {
				uint offset = it.key();
				MarkedExpression value = it.value();

				if (!value.expression->canCompute(this))
					throw AssemblyException(AssemblyException::Error, AssemblyException::Assembling, "Unable to compute expression");

				mWriter.writeBits(offset, value.bitSize, value.expression->compute(this));
				value.expression->deleteLater();
			}
		} catch (const AssemblyException& exception) {
			emit error(exception);
			mErrored = true;
		}
	}

	moveToThread(qApp->thread());
	emit finished();
}

} // namespace tea
