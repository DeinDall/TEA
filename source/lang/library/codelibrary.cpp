#include "codelibrary.h"

#include <QDir>
#include <QFile>

#include <QJsonDocument>
#include <QJsonArray>

#include <algorithm>

namespace tea {

CodeLibrary::CodeLibrary() {}

void CodeLibrary::loadFromDir(QString path) {
	mAccessLock.lockForWrite();

	QDir dir(path);

	if (dir.exists())
		for (QFileInfo fileInfo : dir.entryInfoList())
			if (fileInfo.completeSuffix() == "code.json")
				addFromJsonFile_(fileInfo.absoluteFilePath());
	sort_();

	mAccessLock.unlock();
}

const CodeTemplate* CodeLibrary::findCodeTemplate(QString name, uint argCount) const {
	const CodeTemplate* result = nullptr;

	mAccessLock.lockForRead();

	for (const CodeTemplate& codeTemplate : mTemplates) {
		if (codeTemplate.parameterCount() != argCount)
			continue;
		if (codeTemplate.name() != name)
			continue;

		result = &codeTemplate;
		break;
	}

	mAccessLock.unlock();

	return result;
}

const CodeTemplate* CodeLibrary::findCodeTemplate(QString name) const {
	const CodeTemplate* result = nullptr;

	mAccessLock.lockForRead();

	for (const CodeTemplate& codeTemplate : mTemplates) {
		if (codeTemplate.name() != name)
			continue;

		result = &codeTemplate;
		break;
	}

	mAccessLock.unlock();

	return result;
}

const CodeTemplate& CodeLibrary::findTemplate(ROMRef ref, QString type) const {
	for (const CodeTemplate& codeTemplate : mTemplates) {
		if (codeTemplate.type() != type)
			continue;

		if (codeTemplate.checkAgainst(ref))
			return codeTemplate;
	}

	return mInvalidTemplate;
}

const CodeTemplate& CodeLibrary::findTemplate(QString name, QString type) const {
	for (const CodeTemplate& codeTemplate : mTemplates) {
		if (codeTemplate.name() != name)
			continue;
		if (!codeTemplate.type().contains(type))
			continue;
		return codeTemplate;
	}

	return mInvalidTemplate;
}

const CodeTemplate& CodeLibrary::findTemplate(QString name, uint argCount) const {
	for (const CodeTemplate& codeTemplate : mTemplates) {
		if (codeTemplate.parameterCount() != argCount)
			continue;
		if (codeTemplate.name() != name)
			continue;
		return codeTemplate;
	}

	return mInvalidTemplate;
}

const CodeTemplate& CodeLibrary::findTemplate(QString name) const {
	for (const CodeTemplate& codeTemplate : mTemplates)
		if (codeTemplate.name() == name)
			return codeTemplate;
	return mInvalidTemplate;
}

void CodeLibrary::addFromJsonFile_(QString fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
		return;

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();

	if (doc.isArray()) {
		for (QJsonValue value : doc.array()) {
			if (value.isObject())
				mTemplates.append(CodeTemplate::fromJsonObject(value.toObject()));
			// TODO: else err away
		}
	}
}

void CodeLibrary::sort_() {
	std::sort(mTemplates.begin(), mTemplates.end(), [] (const CodeTemplate& first, const CodeTemplate& second) {
		return first.priority() > second.priority();
	});
}

qint64 CodeLibrary::makeNumberFromJsonValue(QJsonValue value) const {
	if (value.isDouble())
		return value.toInt();
	return value.toString().toLongLong(nullptr, 0);
}

} // namespace tea
