#include "value.h"

namespace tea {

Value::Value()
	: mValue(UINT64_MAX) {}

Value::Value(QString name)
	: mName(name), mValue(UINT64_MAX) {}

bool Value::isValid() const {
	if (mName.isEmpty())
		return false;
	return mType.isValid();
}

void Value::setType(CodeParameterType type) {
	mType = type;
}

void Value::setValue(quint64 value) {
	mValue = value;
}

QString Value::name() const {
	return mName;
}

CodeParameterType Value::type() const {
	return mType;
}

quint64 Value::value() const {
	return mValue;
}

} // namespace tea
