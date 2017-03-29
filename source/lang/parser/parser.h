#ifndef TEA_PARSER_H
#define TEA_PARSER_H

#include <QObject>
#include <QQueue>

#include "lang/error/assemblyexception.h"

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
		bool checkNext(Token::Type type) const;
		Token peekNext() const;
		Token removeNext();
		bool removeNext(Token::Type type);

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
	void statementReady(tea::AbstractStatement* statement);
	void error(tea::AssemblyException exception);
	void finished();

public slots:
	void handleToken(tea::Token token);
	void finishParsing();

private:
	bool mErrored;

	const CodeLibrary* mCodeLibrary;
	TokenQueue mTokenQueue;

	QMap<Token::Type, StartParselet*> mStartParselets;
	QMap<Token::Type, NextParselet*> mNextParselets;
};

} // namespace tea

#endif // TEA_PARSER_H
