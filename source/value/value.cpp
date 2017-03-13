#include "value.h"

namespace tea {

Value::Value()
	: mValue(UINT64_MAX) {}

Value::Value(QString name)
	: mName(name), mValue(UINT64_MAX) {}

bool Value::isValid() const {
	if (mName.isEmpty())
		return false;

	if (mTypes.isEmpty())
		return false;

	return true;
}

void Value::setTypes(QStringList types) {
	mTypes = types;
}

void Value::setValue(quint64 value) {
	mValue = value;
}

QString Value::name() const {
	return mName;
}

QStringList Value::types() const {
	return mTypes;
}

quint64 Value::value() const {
	return mValue;
}

} // namespace tea
