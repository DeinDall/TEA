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

const CodeTemplate& CodeTemplateLibrary::findTemplate(ROMRef ref, QString type) const {
	for (const CodeTemplate& codeTemplate : mTemplates) {
		if (codeTemplate.type() != type)
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
		if (!codeTemplate.type().contains(type))
			continue;
		return codeTemplate;
	}

	return mInvalidTemplate;
}

const CodeTemplate& CodeTemplateLibrary::findTemplate(QString name, uint argCount) const {
	for (const CodeTemplate& codeTemplate : mTemplates) {
		if (codeTemplate.parameterCount() != argCount)
			continue;
		if (codeTemplate.name() != name)
			continue;
		return codeTemplate;
	}

	return mInvalidTemplate;
}

const CodeTemplate& CodeTemplateLibrary::findTemplate(QString name) const {
	for (const CodeTemplate& codeTemplate : mTemplates)
		if (codeTemplate.name() == name)
			return codeTemplate;
	return mInvalidTemplate;
}

void CodeTemplateLibrary::addFromJsonFile_(QString fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
		return;

	QJsonParseError* err = new QJsonParseError;

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), err);
	file.close();

	if (err->error != QJsonParseError::NoError) {
		throw std::runtime_error(std::string("error while parsing json file ")
							 .append(fileName.toStdString()).append(" at pos ").append(std::to_string(err->offset))
							 .append(": ").append(err->errorString().toStdString()));
	}

	if (doc.isArray()) {
		for (QJsonValue value : doc.array()) {
			if (value.isObject())
				mTemplates.append(CodeTemplate::fromJsonObject(value.toObject()));
			// TODO: else err away
		}
	}
}

void CodeTemplateLibrary::sort_() {
	std::sort(mTemplates.begin(), mTemplates.end(), [] (const CodeTemplate& first, const CodeTemplate& second) {
		return first.priority() > second.priority();
	});
}

qint64 CodeTemplateLibrary::makeNumberFromJsonValue(QJsonValue value) const {
	if (value.isDouble())
		return value.toInt();
	return value.toString().toLongLong(nullptr, 0);
}

} // namespace tea
