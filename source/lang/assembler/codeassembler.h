#ifndef TEA_CODEASSEMBLER_H
#define TEA_CODEASSEMBLER_H

#include "core/rom/romwritelayer.h"
#include "lang/valuelibrary.h"

#include "lang/error/assemblyexception.h"

#include <QObject>
#include <QMap>

namespace tea {

class AbstractStatement;
class AbstractExpression;

class CodeAssembler : public QObject {
	Q_OBJECT
public:
	struct MarkedExpression {
		quint64 bitSize;
		AbstractExpression* expression;
	};

public:
	CodeAssembler(const ROM* rom, ValueLibrary* valLib, QObject* parent = nullptr);

	void markExpressionUsage(quint64 offset, quint64 size, AbstractExpression* expression);
	void writeData(const QByteArray data);

	void defineValue(QString name, quint64 value);

	bool hasValue(QString name) const;
	quint64 getValue(QString name) const;

	void setCurrentOffset(uint offset);
	uint currentOffset() const;

	const ROMWriteLayer& writeLayer() const;

signals:
	void error(tea::AssemblyException exception);
	void finished();

public slots:
	void handleStatement(tea::AbstractStatement* statement);
	void finishAssembling();

private:
	bool mErrored;

	uint mCurrentOffset;
	ROMWriteLayer mWriter;

	QMap<uint, MarkedExpression> mMarkedExpression;
	ValueLibrary mValueLibrary;
};

} // namespace tea

#endif // TEA_CODEASSEMBLER_H
