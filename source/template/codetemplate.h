#ifndef TEA_CODETEMPLATE_H
#define TEA_CODETEMPLATE_H

#include <QString>
#include <QList>

#include "rom/romref.h"
#include "code/code.h"

#include "codetemplatecomponent.h"

namespace tea {

class CodeTemplate {
public:
	CodeTemplate();
	CodeTemplate(QString name);

	bool isValid() const;

	void setTypes(QStringList types);
	void setNextTypes(QStringList nexts);
	void setSize(int size);
	void setPriority(int priority);
	void setComponents(QList<CodeTemplateComponent> components);

	QString name() const;
	QStringList types() const;
	QStringList nextTypes() const;
	int size() const;
	int priority() const;
	QList<CodeTemplateComponent> components() const;

	bool checkAgainst(ROMRef ref) const;
	Code makeCodeFrom(ROMRef ref) const;

	inline operator bool () const { return isValid(); }

private:
	QString mName;
	QStringList mTypes;
	QStringList mNexts;

	int mSize;
	int mPriority;

	QList<CodeTemplateComponent> mComponents;
};

} // namespace tea

#endif // TEA_CODETEMPLATE_H
