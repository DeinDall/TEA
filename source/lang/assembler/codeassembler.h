#ifndef TEA_CODEASSEMBLER_H
#define TEA_CODEASSEMBLER_H

#include "lang/core/expression/abstractexpression.h"
#include "core/rom/romwriter.h"
#include "lang/valuelibrary.h"

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

	void markValueUsage(uint offset, uint size, QString valueName);
	void writeData(const QByteArray data);

	void defineValue(QString name, quint64 value);

	void setCurrentOffset(uint offset);
	uint currentOffset() const;

	void outputToFile(QString fileName);

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
