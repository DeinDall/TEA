#ifndef TEA_CODETEMPLATE_H
#define TEA_CODETEMPLATE_H

#include <QString>
#include <QVector>

#include <QJsonObject>

#include "core/rom/romref.h"
#include "codeparametertype.h"
#include "lang/print/printhint.h"

namespace tea {

class CodeTemplate {
public:
	struct Parameter {
		Parameter();

		void fillBits(quint64 value, QByteArray& array) const;
		quint64 readBits(const ROMRef& ref) const;

		CodeParameterType type;
		QString name;

		int bitOffset;
		int bitSize;

		int bitPartSize;

		bool isTuple;
	};

public:
	CodeTemplate();

	bool isValid() const;

	QString name() const;

	QString type() const;
	QString nextType() const;

	uint size() const;

	int priority() const;

	const QVector<Parameter>& parameters() const;
	uint parameterCount() const;

	PrintHint printHint() const;

	QByteArray fixedMask() const;
	QByteArray fixedData() const;

	bool checkAgainst(ROMRef ref) const;

	inline operator bool () const { return isValid(); }

public:
	static CodeTemplate fromJsonObject(QJsonObject object);

protected:
	void setSize(int size);
	uint appendFromJsonObject(QJsonObject object, uint currentOffset);

private:
	QString mName;

	QString mType;
	QString mNext;

	PrintHint mPrintHint;

	int mPriority;

	QByteArray mFixedBytesMask;
	QByteArray mFixedBytesValue;

	QVector<Parameter> mParameters;
};

} // namespace tea

#endif // TEA_CODETEMPLATE_H
