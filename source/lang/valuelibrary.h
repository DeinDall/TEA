#ifndef TEA_VALUELIBRARY_H
#define TEA_VALUELIBRARY_H

#include <QJsonObject>

#include "lang/core/code/codeparametertype.h"
#include "lang/core/value/value.h"

namespace tea {

class ValueLibrary {
public:
	ValueLibrary();

	void loadFromDir(QString path);

	void addValue(QString name, QString type, quint64 value);

	const Value& findValue(const CodeParameterType& type, quint64 value) const;
	const Value& findValue(QString name) const;

protected:
	void addFromJsonFile_(QString file);

	Value makeFromJsonObject_(QJsonObject object);

private:
	QList<Value> mValues;
	Value mInvalidValue;
};

} // namespace tea

#endif // TEA_VALUELIBRARY_H
