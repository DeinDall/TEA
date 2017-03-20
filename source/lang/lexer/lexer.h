#ifndef TEA_LEXER_H
#define TEA_LEXER_H

#include <QString>
#include <QObject>

#include "lang/core/token.h"

namespace tea {

class Lexer : public QObject {
	Q_OBJECT
public:
	Lexer();

	void tokenize(QStringRef ref);

protected:
	void tokenizeSpace(QStringRef ref);
	void tokenizeNumber(QStringRef ref);
	void tokenizeIdentifier(QStringRef ref);
	void tokenizeString(QStringRef ref);
	void tokenizeSymbol(QStringRef ref);

signals:
	void tokenReady(Token token);
	void tokenError(QStringRef where, QString what);
	void finished();

public slots:
	void handleLine(QString line);
	void finishLexing();

private:
};

} // namespace tea

#endif // TEA_LEXER_H
