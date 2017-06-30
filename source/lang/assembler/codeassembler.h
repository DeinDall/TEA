#ifndef TEA_CODEASSEMBLER_H
#define TEA_CODEASSEMBLER_H

#include "core/rom/romwriter.h"
#include "lang/valuelibrary.h"

#include <QObject>
#include <QMap>

namespace tea {

class AStatement;
class AExpression;

class CodeAssembler : public QObject {
	Q_OBJECT
public:
	struct MarkedExpression {
		quint64 bitSize;
		AExpression* expression;
	};

public:
	CodeAssembler(const ROM* rom, ValueLibrary* valLib, QObject* parent = nullptr);

	void markExpressionUsage(quint64 offset, quint64 size, AExpression* expression);
	void writeData(const QByteArray data);

	void defineValue(QString name, quint64 value);

	bool hasValue(QString name) const;
	quint64 getValue(QString name) const;

	void setCurrentOffset(uint offset);
	uint currentOffset() const;

	void outputToFile(QString fileName);

public slots:
	void handleStatement(AStatement* statement);

private:
	uint mCurrentOffset;
	ROMWriter mWriter;

	QMap<uint, MarkedExpression> mMarkedExpression;
	ValueLibrary mValueLibrary;
};

} // namespace tea

#endif // TEA_CODEASSEMBLER_H
