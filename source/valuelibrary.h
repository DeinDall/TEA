#ifndef TEA_VALUELIBRARY_H
#define TEA_VALUELIBRARY_H

#include <QJsonObject>

#include "value/value.h"

namespace tea {

class ValueLibrary {
public:
	ValueLibrary();

	void loadFromDir(QString path);

	void addValue(QString name, QString type, quint64 value);

	const Value& findValueFor(QStringList types, quint64 value) const;

protected:
	void addFromJsonFile_(QString file);

	Value makeFromJsonObject_(QJsonObject object);

private:
	QList<Value> mValues;
	Value mInvalidValue;
};

} // namespace tea

#endif // TEA_VALUELIBRARY_H
