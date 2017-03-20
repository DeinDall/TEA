#ifndef TEA_LEXER_H
#define TEA_LEXER_H

#include <QString>
#include <QObject>

#include "lang/core/token.h"

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
	void tokenReady(Token token);
	void tokenError(QStringRef where, QString what);
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
