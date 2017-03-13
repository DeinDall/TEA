#ifndef TEA_CODEASSEMBLER_H
#define TEA_CODEASSEMBLER_H

#include "lang/expression/abstractexpression.h"
#include "rom/romwriter.h"
#include "valuelibrary.h"

#include <QObject>
#include <QMap>

namespace tea {

class CodeAssembler : public QObject {
	Q_OBJECT
public:
	struct MarkedValue {
		uint size;
		QString name;
	};

public:
	CodeAssembler(const ROM* rom, ValueLibrary* valLib, QObject* parent = nullptr);

	void markValue(uint offset, uint size, QString valueName);
	void writeData(const QByteArray data);
	void setCurrentOffset(uint offset);

	void defineValue(QString name, quint64 value);

	uint currentOffset() const;

	void writeToFile(QString fileName);

public slots:
	void handleExpression(AbstractExpression* exp);

private:
	uint mCurrentOffset;
	ROMWriter mWriter;

	QMap<uint, MarkedValue> mMarkedValues;
	ValueLibrary mValueLibrary;
};

} // namespace tea

#endif // TEA_CODEASSEMBLER_H
