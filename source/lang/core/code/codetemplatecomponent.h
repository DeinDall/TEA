#ifndef TEA_CODETEMPLATECOMPONENT_H
#define TEA_CODETEMPLATECOMPONENT_H

#include "codeparametertype.h"

namespace tea {

class CodeTemplateComponent {
public:
	CodeTemplateComponent(QString name);

	void setType(CodeParameterType type);
	void setOffset(int offset);
	void setSize(int size);
	void setFixedValue(quint64 value);

	QString name() const;
	const CodeParameterType& type() const;

	int offset() const;
	int size() const;

	bool isFixed() const;
	quint64 fixedValue() const;

private:
	QString mName;
	CodeParameterType mType;

	int mOffset;
	int mSize;

	bool mFixed;
	quint64 mFixedValue;
};

} // namespace tea

#endif // TEA_CODETEMPLATECOMPONENT_H
