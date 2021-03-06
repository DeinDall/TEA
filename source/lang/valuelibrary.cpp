#include "valuelibrary.h"

#include <QDir>

#include <QJsonDocument>
#include <QJsonArray>

namespace tea {

ValueLibrary::ValueLibrary() {}

void ValueLibrary::loadFromDir(QString path) {
	QDir dir(path);

	if (dir.exists())
		for (QFileInfo fileInfo : dir.entryInfoList())
			if (fileInfo.completeSuffix() == "values.json")
				addFromJsonFile_(fileInfo.absoluteFilePath());
}

void ValueLibrary::addValue(QString name, QString type, quint64 value) {
	Value val(name);

	val.setType(CodeParameterType::parseFromString(type));
	val.setValue(value);

	mValues.append(val);
}

const Value& ValueLibrary::findValue(const CodeParameterType& type, quint64 value) const {
	for (const Value& val : mValues) {
		if (val.value() != value)
			continue;
		if (type.name() != val.type().name())
			continue;

		auto it = type.parameters().begin();
		bool mismatched = false;

		while (it != type.parameters().end()) {
			QString arg = it.key();

			for (QString values : val.type().parameterValues(arg))
				if (!it.value().contains(values)) {
					mismatched = true;
					break;
				}

			++it;
		}

		if (mismatched)
			continue;

		return val;
	}

	return mInvalidValue;
}

const Value& ValueLibrary::findValue(QString name) const {
	for (const Value& val : mValues)
		if (val.name() == name)
			return val;
	return mInvalidValue;
}

void ValueLibrary::addFromJsonFile_(QString fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
		return;

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();

	if (doc.isArray()) {
		for (QJsonValue value : doc.array()) {
			if (value.isObject())
				mValues.append(makeFromJsonObject_(value.toObject()));
			// TODO: else err away
		}
	}
}

Value ValueLibrary::makeFromJsonObject_(QJsonObject object) {
	Value result(object.value("name").toString());

	if (object.contains("type"))
		result.setType(CodeParameterType::parseFromString(object.value("type").toString()));

	if (object.contains("value")) {
		QJsonValue value = object.value("value");

		if (value.isDouble())
			result.setValue(value.toInt());
		else if (value.isString())
			result.setValue(value.toString().toLongLong(nullptr, 0));
	}

	return result;
}

} // namespace tea
