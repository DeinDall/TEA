#include "disassemblerstate.h"

namespace tea {

DisassemblerState::DisassemblerState() {}

void DisassemblerState::setArgument(QString name, QString value) {
	mCurrentArguments[name] = value;
}

QString DisassemblerState::getArgument(QString name, QString defaultValue) const {
	auto it = mCurrentArguments.find(name);

	if (it != mCurrentArguments.end())
		return it.value();

	return defaultValue;
}

QString DisassemblerState::parseArgument(QString arg) const {
	if (arg.isEmpty())
		return arg;

	if (!arg.contains('='))
		return arg;

	QStringList args = arg.split('=');

	if (args.size() != 2)
		return arg;

	if (args.at(0).isEmpty())
		return arg;

	if (args.at(0).at(0) == '$')
		return getArgument(args.at(0).mid(1), args.at(1));

	return arg;
}

} // namespace tea
