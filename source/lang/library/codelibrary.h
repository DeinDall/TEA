#ifndef TEA_CODELIBRARY_H
#define TEA_CODELIBRARY_H

#include "lang/core/code/codetemplate.h"

#include <QJsonObject>
#include <QReadWriteLock>

namespace tea {

class CodeLibrary {
public:
	CodeLibrary();

	void loadFromDir(QString path);

	const CodeTemplate* findCodeTemplate(QString name, uint argCount) const;
	const CodeTemplate* findCodeTemplate(QString name) const;

	const CodeTemplate& findTemplate(ROMRef ref, QString type) const;
	const CodeTemplate& findTemplate(QString name, QString type) const;
	const CodeTemplate& findTemplate(QString name, uint argCount) const;
	const CodeTemplate& findTemplate(QString name) const;

protected:
	void addFromJsonFile_(QString fileName);
	void sort_();

	qint64 makeNumberFromJsonValue(QJsonValue value) const;

private:
	QReadWriteLock mAccessLock;

	CodeTemplate mInvalidTemplate;
	QList<CodeTemplate> mTemplates;
};

} // namespace tea

#endif // TEA_CODELIBRARY_H
