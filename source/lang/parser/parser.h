#ifndef TEA_PARSER_H
#define TEA_PARSER_H

#include <QObject>
#include <QQueue>

#include "lang/core/statement/abstractstatement.h"
#include "lang/core/token.h"

#include "parselet/startparselet.h"
#include "parselet/nextparselet.h"

#include "lang/library/codelibrary.h"

namespace tea {

class Parser : public QObject {
	Q_OBJECT

public:
	class TokenQueue {
		friend class Parser;

	public:
		bool checkNext(Token::TokenType type) const;
		Token peekNext() const;
		Token removeNext();
		bool removeNext(Token::TokenType type);

	private:
		QQueue<Token> mTokens;
	};
public:
	Parser(const CodeLibrary* lib, QObject* parent = nullptr);
	~Parser();

	void setCodeLibrary(const CodeLibrary* lib);

	TokenQueue& tokens();
	AbstractExpression* parseExpression(int precedence = 0);

protected:
	void parseLabel();
	void parseStatement();

	QList<AbstractExpression*> parseArguments();

	QObject* returnParent();

signals:
	void statementReady(AbstractStatement* statement);
	void parseError(QString what);
	void finished();

public slots:
	void handleToken(Token token);
	void finishParsing();

protected slots:
	void onError();

private:
	bool mErrored;

	const CodeLibrary* mCodeLibrary;
	TokenQueue mTokenQueue;

	QMap<Token::TokenType, StartParselet*> mStartParselets;
	QMap<Token::TokenType, NextParselet*> mNextParselets;
};

} // namespace tea

#endif // TEA_PARSER_H
