#include "codetemplatelibrary.h"

#include <QDir>
#include <QFile>

#include <QJsonDocument>
#include <QJsonArray>

#include <algorithm>

namespace tea {

CodeTemplateLibrary::CodeTemplateLibrary() {}

void CodeTemplateLibrary::loadFromDir(QString path) {
	QDir dir(path);

	if (dir.exists())
		for (QFileInfo fileInfo : dir.entryInfoList())
			if (fileInfo.completeSuffix() == "code.json")
				addFromJsonFile_(fileInfo.absoluteFilePath());
	sort_();
}

const CodeTemplate& CodeTemplateLibrary::findTemplateFor(ROMRef ref, QString type) const {
	for (const CodeTemplate& codeTemplate : mTemplates) {
		if (!codeTemplate.types().contains(type))
			continue;

		if (codeTemplate.checkAgainst(ref))
			return codeTemplate;
	}

	return mInvalidTemplate;
}

const CodeTemplate& CodeTemplateLibrary::findTemplate(QString name, QString type) const {
	for (const CodeTemplate& codeTemplate : mTemplates) {
		if (codeTemplate.name() != name)
			continue;
		if (!codeTemplate.types().contains(type))
			continue;
		return codeTemplate;
	}

	return mInvalidTemplate;
}

void CodeTemplateLibrary::addFromJsonFile_(QString fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
		return;

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();

	if (doc.isArray()) {
		for (QJsonValue value : doc.array()) {
			if (value.isObject())
				mTemplates.append(makeTemplateFromJsonObject(value.toObject()));
			// TODO: else err away
		}
	}
}

void CodeTemplateLibrary::sort_() {
	std::sort(mTemplates.begin(), mTemplates.end(), [] (const CodeTemplate& first, const CodeTemplate& second) {
		return first.priority() > second.priority();
	});
}

CodeTemplate CodeTemplateLibrary::makeTemplateFromJsonObject(QJsonObject object) const {
	CodeTemplate result(object.value("name").toString());

	if (object.contains("type"))
		result.setTypes(object.value("type").toString().split(' '));

	if (object.contains("next"))
		result.setNextTypes(object.value("next").toString().split(' '));

	if (object.contains("size"))
		result.setSize(makeNumberFromJsonValue(object.value("size")));

	if (object.contains("printHint")) {
		QString str = object.value("printHint").toString();

		if (str == "beginScope")
			result.setPrintHint(PrintHint(PrintHint::Continue, PrintHint::OpenScope));
		else if (str == "endScope")
			result.setPrintHint(PrintHint(PrintHint::CloseScope, PrintHint::Continue));
		else if (str == "endPart")
			result.setPrintHint(PrintHint(PrintHint::Continue, PrintHint::IgnoreScope));
	}

	if (object.contains("priority")) {
		QJsonValue value = object.value("priority");

		if (value.isDouble())
			result.setPriority(value.toInt());
		else if (value.isString()) {
			QString str = value.toString();

			if (str == "high")
				result.setPriority(100);
			else if (str == "low")
				result.setPriority(-100);
			else
				result.setPriority(str.toInt(nullptr, 0));
		}
	}

	QList<CodeTemplateComponent> components;

	if (object.contains("components")) {
		QJsonValue arrayValue = object.value("components");
		int currentOffset = 0;

		if (arrayValue.isArray()) {
			for (QJsonValue value : arrayValue.toArray()) {
				QJsonObject componentObject = value.toObject();
				CodeTemplateComponent component = makeTemplateComponentFromJsonObject(componentObject);

				if (componentObject.contains("offset"))
					component.setOffset(makeNumberFromJsonValue(componentObject.value("offset")));
				else
					component.setOffset(currentOffset);
				currentOffset = component.offset() + component.size();

				components.append(component);
			}
		}
	}

	result.setComponents(components);
	return result;
}

CodeTemplateComponent CodeTemplateLibrary::makeTemplateComponentFromJsonObject(QJsonObject object) const {
	CodeTemplateComponent result(object.value("name").toString());

	if (object.contains("type"))
		result.setTypes(object.value("type").toString().split(' '));

	if (object.contains("size"))
		result.setSize(makeNumberFromJsonValue(object.value("size")));

	if (object.contains("fixed") && object.value("fixed").toBool()) {
		if (object.contains("value"))
			result.setFixedValue(makeNumberFromJsonValue(object.value("value")));
		else
			result.setFixedValue(0);
	}

	return result;
}

qint64 CodeTemplateLibrary::makeNumberFromJsonValue(QJsonValue value) const {
	if (value.isDouble())
		return value.toInt();
	return value.toString().toLongLong(nullptr, 0);
}

} // namespace tea
