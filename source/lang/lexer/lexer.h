#ifndef TEA_LEXER_H
#define TEA_LEXER_H

#include <QString>
#include <QObject>

#include "lang/core/itokensource.h"
#include "lexelets/ilexelet.h"

namespace tea {

class Lexer : public QObject/*, public ITokenSource*/ {
	Q_OBJECT

public:
	using charCheckFunc_t = bool(*)(QChar);

public:
	Lexer(QObject* parent = nullptr);
	~Lexer();

	// Token nextToken();
	// Token peekToken();

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

public slots:
	void debugToken(Token token);

private:
//	QVector<QPair<charCheckFunc_t, ILexelet*>> mLexelets;
};

} // namespace tea

#endif // TEA_LEXER_H
