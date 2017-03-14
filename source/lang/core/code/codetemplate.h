#ifndef TEA_CODETEMPLATE_H
#define TEA_CODETEMPLATE_H

#include <QString>
#include <QList>

#include "core/rom/romref.h"
#include "lang/core/code/code.h"
#include "lang/print/printhint.h"

#include "codetemplatecomponent.h"

namespace tea {

class CodeTemplate {
public:
	CodeTemplate();
	CodeTemplate(QString name);

	bool isValid() const;

	void setType(QString type);
	void setNextType(QString next);
	void setSize(int size);
	void setPriority(int priority);
	void setComponents(QList<CodeTemplateComponent> components);
	void setPrintHint(PrintHint hint);

	QString name() const;
	QStringList types() const;
	QString nextType() const;
	int size() const;
	int priority() const;
	const QList<CodeTemplateComponent>& components() const;
	PrintHint printHint() const;

	uint argumentCount() const;

	bool checkAgainst(ROMRef ref) const;
	Code makeCodeFrom(ROMRef ref) const;

	inline operator bool () const { return isValid(); }

private:
	QString mName;
	QString mType;
	QString mNext;
	PrintHint mPrintHint;

	int mSize;
	int mPriority;

	QList<CodeTemplateComponent> mComponents;
};

} // namespace tea

#endif // TEA_CODETEMPLATE_H
