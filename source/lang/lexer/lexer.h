#ifndef TEA_LEXER_H
#define TEA_LEXER_H

#include <QString>
#include <QObject>

#include "lang/core/token.h"
#include "lang/error/assemblyexception.h"

namespace tea {

class Lexer : public QObject {
	Q_OBJECT
public:
	Lexer(QObject* parent = nullptr);

	QStringRef tokenize(QStringRef ref);

protected:
	QStringRef tokenizeSpace(QStringRef ref);
	QStringRef tokenizeNumber(QStringRef ref);
	QStringRef tokenizeIdentifier(QStringRef ref);
	QStringRef tokenizeString(QStringRef ref);
	QStringRef tokenizeSymbol(QStringRef ref);

signals:
	void tokenReady(tea::Token token);
	void error(tea::AssemblyException exception);
	void finished();

public slots:
	void handleLine(QString line);
	void finishLexing();

protected slots:
	void onError();

private:
	bool mErrored;
};

} // namespace tea

#endif // TEA_LEXER_H
