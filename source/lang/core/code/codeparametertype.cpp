#include "codeparametertype.h"

namespace tea {

CodeParameterType::CodeParameterType() {}

CodeParameterType::CodeParameterType(QString name)
	: mTypeName(name) {}

bool CodeParameterType::isValid() const {
	return ((!mTypeName.isEmpty()) && (mTypeName != "null"));
}

QString CodeParameterType::name() const {
	return mTypeName;
}

QStringList CodeParameterType::parameterValues(QString parameter) const {
	auto it = mArguments.find(parameter);

	if (it != mArguments.end())
		return it.value();

	return QStringList();
}

CodeParameterType CodeParameterType::parseFromString(QString str) {
	QStringList stringList = str.simplified().split(' ');

	if (stringList.isEmpty())
		return CodeParameterType("null");

	QString name = stringList.first();
	stringList.removeFirst();

	CodeParameterType result(name);

	for (QString argument : stringList) {
		QStringList argList = argument.split(':');

		if (argList.size() == 2)
			result.mArguments[argList.at(0)].append(argList.at(1));
		// TODO: else err away
	}

	return result;
}

const QMap<QString, QStringList>& CodeParameterType::parameters() const {
	return mArguments;
}

} // namespace tea
