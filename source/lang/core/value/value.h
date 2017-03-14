#ifndef TEA_VALUE_H
#define TEA_VALUE_H

#include <QStringList>

namespace tea {

class Value {
public:
	Value();
	Value(QString name);

	bool isValid() const;

	void setTypes(QStringList types);
	void setValue(quint64 value);

	QString name() const;
	QStringList types() const;
	quint64 value() const;

	inline operator bool () const { return isValid(); }

private:
	QString mName;
	QStringList mTypes;
	quint64 mValue;
};

} // namespace tea

#endif // TEA_VALUE_H
