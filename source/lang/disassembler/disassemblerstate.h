#ifndef TEA_DISASSEMBLERSTATE_H
#define TEA_DISASSEMBLERSTATE_H

#include <QString>
#include <QMap>

namespace tea {

class DisassemblerState {
public:
	DisassemblerState();

	void setArgument(QString name, QString value);
	QString getArgument(QString name, QString defaultValue) const;

	QString parseArgument(QString arg) const;

private:
	QMap<QString, QString> mCurrentArguments;
};

} // namespace tea

#endif // TEA_DISASSEMBLERSTATE_H
