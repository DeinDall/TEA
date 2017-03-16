#include "codetemplate.h"

#include <QJsonArray>
#include <QJsonValue>

#include "core/rom/romutil.h"

namespace tea {

CodeTemplate::Parameter::Parameter()
	: offset(0), size(0) {}

CodeTemplate::CodeTemplate()
	:  mNext("null"), mPriority(0) {}

bool CodeTemplate::isValid() const {
	if (mName.isEmpty())
		return false;

	if (size() == 0)
		return false;

	if (mType.isEmpty())
		return false;

	return true;
}

QString CodeTemplate::name() const {
	return mName;
}

QString CodeTemplate::type() const {
	return mType;
}

QString CodeTemplate::nextType() const {
	return mNext;
}

uint CodeTemplate::size() const {
	return mFixedBytesMask.size();
}

int CodeTemplate::priority() const {
	return mPriority;
}

const QVector<CodeTemplate::Parameter>& CodeTemplate::parameters() const {
	return mParameters;
}

PrintHint CodeTemplate::printHint() const {
	return mPrintHint;
}

uint CodeTemplate::parameterCount() const {
	return mParameters.size();
}

QByteArray CodeTemplate::fixedMask() const {
	return mFixedBytesMask;
}

QByteArray CodeTemplate::fixedData() const {
	return mFixedBytesValue;
}

bool CodeTemplate::checkAgainst(ROMRef ref) const {
	auto refIt = ref.begin();
	auto maskIt = mFixedBytesMask.begin();
	auto valueIt = mFixedBytesValue.begin();

	if (ref.size() < size())
		return false;

	while (valueIt != mFixedBytesValue.end()) {
		if (((*refIt) & (*maskIt)) != ((*valueIt) & (*maskIt)))
			return false;

		++refIt;
		++maskIt;
		++valueIt;
	}

	return true;
}

CodeTemplate CodeTemplate::fromJsonObject(QJsonObject object) {
	CodeTemplate result;
	QJsonValue value;

	value = object.value("name");
	if (value.isString())
		result.mName = value.toString();

	value = object.value("type");
	if (value.isString())
		result.mType = value.toString();

	value = object.value("next");
	if (value.isString())
		result.mNext = value.toString();

	value = object.value("size");
	if (value.isString())
		result.setSize(value.toString().toInt(nullptr, 0));
	else if (value.isDouble())
		result.setSize(value.toInt());

	value = object.value("printHint");
	if (value.isString()) {
		QString str = value.toString();

		if (str == "beginScope")
			result.mPrintHint = PrintHint(PrintHint::CloseScope, PrintHint::OpenScope);
		else if (str == "endScope")
			result.mPrintHint = PrintHint(PrintHint::CloseScope, PrintHint::Continue);
		else if (str == "endPart")
			result.mPrintHint = PrintHint(PrintHint::Continue, PrintHint::IgnoreScope);
	}

	value = object.value("priority");
	if (value.isString()) {
		QString str = value.toString();

		if (str == "high")
			result.mPriority = 100;
		else if (str == "low")
			result.mPriority = -100;
		else
			result.mPriority = str.toInt(nullptr, 0);
	} else if (value.isDouble())
		result.mPriority = value.toInt();

	value = object.value("components");
	if (value.isArray()) {
		int currentOffset = 0;

		for (QJsonValue componentValue : value.toArray()) {
			if (componentValue.isObject()) {
				QJsonObject componentObject = componentValue.toObject();
				currentOffset = result.appendFromJsonObject(componentObject, currentOffset);
			}
		}
	}

	return result;
}

void CodeTemplate::setSize(int size) {
	mFixedBytesMask.fill(0x00, size);
	mFixedBytesValue.fill(0x00, size);
}

uint CodeTemplate::appendFromJsonObject(QJsonObject object, uint currentOffset) {
	QJsonValue value;

	uint size = 0;
	uint offset = currentOffset;

	value = object.value("size");
	if (value.isString())
		size = value.toString().toInt(nullptr, 0);
	else if (value.isDouble())
		size = value.toInt();

	value = object.value("offset");
	if (value.isString())
		offset = value.toString().toInt(nullptr, 0);
	else if (value.isDouble())
		offset = value.toInt();

	value = object.value("fixed");
	if (value.isBool() && value.toBool()) {
		quint64 fixedValue = UINT64_MAX;

		value = object.value("value");
		if (value.isString())
			fixedValue = value.toString().toLongLong(nullptr, 0);
		else if (value.isDouble())
			fixedValue = value.toInt();

		if (fixedValue != UINT64_MAX) {
			mFixedBytesMask.replace(offset, size, QByteArray(size, 0xFF));
			mFixedBytesValue.replace(offset, size, makeNumber(fixedValue, size));
		}
	} else {
		Parameter parameter;

		parameter.offset = offset;
		parameter.size = size;

		value = object.value("name");
		if (value.isString())
			parameter.name = value.toString();

		value = object.value("type");
		if (value.isString())
			parameter.type = CodeParameterType::parseFromString(value.toString());

		mParameters.append(parameter);
	}

	return offset + size;
}

} // namespace tea
