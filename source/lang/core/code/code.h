#ifndef TEA_CODE_H
#define TEA_CODE_H

#include <QVector>

#include "core/rom/romref.h"
#include "lang/valuelibrary.h"

namespace tea {

class CodeTemplate;

class Code {
	friend class CodeTemplate;
public:
	class ConstParameterIterator {
		friend class Code;
	public:
		QString name() const;
		QStringList types() const;
		quint64 value() const;
		uint offset() const;

		bool next();

	protected:
		ConstParameterIterator(const Code* code);

	private:
		const Code* mCode;

		int mParameterIndex;
		int mComponentIndex;
	};

public:
	Code();

	const CodeTemplate* codeTemplate() const;
	uint size() const;

	quint64 parameterValue(uint index) const;
	ConstParameterIterator parameterIterator() const;

protected:
	Code(const CodeTemplate* templte, QVector<quint64> parameters);

private:
	const CodeTemplate* mTemplate;
	QVector<quint64> mParameters;
};

} // namespace tea

#endif // TEA_CODE_H
