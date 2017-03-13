#ifndef TEA_PARSER_H
#define TEA_PARSER_H

#include <QObject>
#include <QVector>

#include "lang/expression/abstractexpression.h"
#include "lexer/token.h"

#include "codetemplatelibrary.h"

namespace tea {

class Parser : public QObject {
	Q_OBJECT
public:
	Parser(const CodeTemplateLibrary* lib, QObject* parent = nullptr);

protected:
	void handleLabel();
	void handleStack();
	AbstractExpression* singleTokenExpression(Token token);

	QObject* expressionParent();

public slots:
	void handleToken(Token token);

signals:
	void expressionReady(AbstractExpression* exp);
	void parseError(QString what);

private:
	const CodeTemplateLibrary* mTemplateLibrary;
	QVector<Token> mCurrentTokens;
};

} // namespace tea

#endif // TEA_PARSER_H
