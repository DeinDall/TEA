#ifndef TEA_CODEPARAMETERTYPE_H
#define TEA_CODEPARAMETERTYPE_H

#include <QString>
#include <QMap>

namespace tea {

class CodeParameterType {
public:
	CodeParameterType();

	bool isValid() const;

	QString name() const;
	QStringList parameterValues(QString parameter) const;
	const QMap<QString, QStringList>& parameters() const;

protected:
	CodeParameterType(QString name);

public:
	static CodeParameterType parseFromString(QString str);

private:
	QString mTypeName;
	QMap<QString, QStringList> mArguments;
};

} // namespace tea

#endif // TEA_CODEPARAMETERTYPE_H
