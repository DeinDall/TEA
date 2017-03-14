#ifndef TEA_VALUE_H
#define TEA_VALUE_H

#include "lang/core/code/codeparametertype.h"

namespace tea {

class Value {
public:
	Value();
	Value(QString name);

	bool isValid() const;

	void setType(CodeParameterType type);
	void setValue(quint64 value);

	QString name() const;
	CodeParameterType type() const;
	quint64 value() const;

	inline operator bool () const { return isValid(); }

private:
	QString mName;
	CodeParameterType mType;
	quint64 mValue;
};

} // namespace tea

#endif // TEA_VALUE_H
