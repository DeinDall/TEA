#ifndef TEA_CODETEMPLATECOMPONENT_H
#define TEA_CODETEMPLATECOMPONENT_H

#include <QStringList>

namespace tea {

class CodeTemplateComponent {
public:
	CodeTemplateComponent(QString name);

	void setTypes(QStringList types);
	void setOffset(int offset);
	void setSize(int size);
	void setFixedValue(quint64 value);

	QString name() const;
	QStringList types() const;

	int offset() const;
	int size() const;

	bool isFixed() const;
	quint64 fixedValue() const;

private:
	QString mName;
	QStringList mTypeList;

	int mOffset;
	int mSize;

	bool mFixed;
	quint64 mFixedValue;
};

} // namespace tea

#endif // TEA_CODETEMPLATECOMPONENT_H
