#ifndef TEA_CODETEMPLATELIBRARY_H
#define TEA_CODETEMPLATELIBRARY_H

#include "template/codetemplate.h"

#include <QJsonObject>

namespace tea {

class CodeTemplateLibrary {
public:
	CodeTemplateLibrary();

	void loadFromDir(QString path);

	const CodeTemplate& findTemplateFor(ROMRef ref, QString type) const;
	const CodeTemplate& findTemplate(QString name, QString type) const;
	const CodeTemplate& findTemplate(QString name, uint argCount) const;
	const CodeTemplate& findTemplate(QString name) const;

protected:
	void addFromJsonFile_(QString fileName);
	void sort_();

	CodeTemplate makeTemplateFromJsonObject(QJsonObject object) const;
	CodeTemplateComponent makeTemplateComponentFromJsonObject(QJsonObject object) const;

	qint64 makeNumberFromJsonValue(QJsonValue value) const;

private:
	CodeTemplate mInvalidTemplate;
	QList<CodeTemplate> mTemplates;
};

} // namespace tea

#endif // TEA_CODETEMPLATELIBRARY_H
