#ifndef TEA_PARSER_H
#define TEA_PARSER_H

#include <QObject>
#include <QVector>

#include "lang/core/statement/abstractstatement.h"
#include "lang/core/token.h"

#include "parselet/startparselet.h"
#include "parselet/nextparselet.h"

#include "lang/codetemplatelibrary.h"

namespace tea {

class Parser : public QObject {
	Q_OBJECT
public:
	Parser(const CodeTemplateLibrary* lib, QObject* parent = nullptr);
	~Parser();

	Token removeNext();
	bool removeNext(Token::TokenType type);
	Token peekNext() const;
	bool checkNext(Token::TokenType type) const;

	AbstractExpression* parseExpression(int precedence = 0);

protected:
	void parseLabel();
	void parseStatement();

	QObject* returnParent();

public slots:
	void handleToken(Token token);

signals:
	void statementReady(AbstractStatement* statement);
	void parseError(QString what);

private:
	const CodeTemplateLibrary* mTemplateLibrary;
	QVector<Token> mCurrentTokens;

	QMap<Token::TokenType, StartParselet*> mStartParselets;
	QMap<Token::TokenType, NextParselet*> mNextParselets;
};

} // namespace tea

#endif // TEA_PARSER_H
