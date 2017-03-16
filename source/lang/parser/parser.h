#ifndef TEA_PARSER_H
#define TEA_PARSER_H

#include <QObject>
#include <QVector>

#include "lang/core/statement/abstractstatement.h"
#include "lang/core/token.h"

#include "lang/codetemplatelibrary.h"

namespace tea {

class Parser : public QObject {
	Q_OBJECT
public:
	Parser(const CodeTemplateLibrary* lib, QObject* parent = nullptr);

protected:
	void parseLabel();
	void parseStatement();

	AbstractExpression* parseExpression();
	AbstractExpression* parseNext(AbstractExpression* previous, int precedence);

	bool checkNext(Token::TokenType type) const;

	QObject* returnParent();

public slots:
	void handleToken(Token token);

signals:
	void statementReady(AbstractStatement* statement);
	void parseError(QString what);

private:
	const CodeTemplateLibrary* mTemplateLibrary;
	QVector<Token> mCurrentTokens;
};

} // namespace tea

#endif // TEA_PARSER_H
