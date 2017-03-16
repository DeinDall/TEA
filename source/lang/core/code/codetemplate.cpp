#include "codetemplate.h"

#include <QJsonArray>
#include <QJsonValue>

#include "core/rom/romutil.h"

namespace tea {

CodeTemplate::Parameter::Parameter()
	: bitOffset(0), bitSize(0), isTuple(false) {}

void CodeTemplate::Parameter::fillBits(quint64 value, QByteArray& array) const {
	value <<= (bitOffset & 0x7);
	quint64 mask = ((0x1 << bitSize)-1) << (bitOffset & 0x7);

	for (int i=(bitOffset >> 3); i<((bitOffset+bitSize+7) >> 3); ++i) {
		array[i] = (array[i] & (~(mask & 0xFF))); // clears the parameter bits
		array[i] = (array[i] | (value & mask & 0xFF)); // fills the parameter bits
		mask >>= 8;
		value >>= 8;
	}
}

quint64 CodeTemplate::Parameter::readBits(const ROMRef& ref) const {
	quint64 mask = ((0x1 << bitSize)-1) << (bitOffset & 0x7);
	quint64 result = 0;

	uint byteOffset = (bitOffset >> 3);
	uint byteSize = ((bitSize+7) >> 3);

	for (int i=0; i<byteSize; ++i)
		result |= ((ref.at(byteOffset+i) & (mask & 0xFF)) << (i*8));

	return (result >> (bitOffset & 0x7));
}

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
	if (value.isString()) {
		QString strValue = value.toString();

		if (strValue.endsWith("bit"))
			size = strValue.leftRef(strValue.size()-3).toInt(nullptr, 0);
		else
			size = 8*strValue.toInt(nullptr, 0);
	} else if (value.isDouble())
		size = 8*value.toInt();

	value = object.value("offset");
	if (value.isString()) {
		QString strValue = value.toString();

		if (strValue.endsWith("bit"))
			offset = strValue.leftRef(strValue.size()-3).toInt(nullptr, 0);
		else
			offset = 8*strValue.toInt(nullptr, 0);
	} else if (value.isDouble())
		offset = 8*value.toInt();

	value = object.value("fixed");
	if (value.isBool() && value.toBool()) {
		quint64 fixedValue = UINT64_MAX;

		value = object.value("value");
		if (value.isString())
			fixedValue = value.toString().toLongLong(nullptr, 0);
		else if (value.isDouble())
			fixedValue = value.toInt();

		if (fixedValue != UINT64_MAX) {
			fixedValue <<= (offset & 0x7);
			quint64 fixedMask = ((0x1 << size)-1) << (offset & 0x7);

			for (uint i=(offset >> 3); i<((offset+size+7) >> 3); ++i) {
				mFixedBytesMask[i] = (mFixedBytesMask[i] | (fixedMask & 0xFF));
				mFixedBytesValue[i] = (mFixedBytesValue[i] | (fixedValue & 0xFF));

				fixedMask >>= 8;
				fixedValue >>= 8;
			}
		}
	} else {
		Parameter parameter;

		parameter.bitOffset = offset;
		parameter.bitSize = size;

		value = object.value("tuple");
		if (value.isBool() && value.toBool())
			parameter.isTuple = true;

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
