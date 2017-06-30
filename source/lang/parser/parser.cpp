#include "parser.h"

#include <QStringBuilder>
#include <QDebug>

#include "lang/core/keywords.h"

#include "parselet/valueparselet.h"
#include "parselet/numberparselet.h"
#include "parselet/tupleparselet.h"

#include "lang/core/expression/numberexpression.h"
#include "lang/core/expression/valueexpression.h"
#include "lang/core/expression/tupleexpression.h"

#include "lang/core/statement/codestatement.h"
#include "lang/core/statement/labelstatement.h"
#include "lang/core/statement/orgstatement.h"

namespace tea {

Parser::Parser(const CodeTemplateLibrary* lib, QObject* parent)
	: QObject(parent), mTemplateLibrary(lib) {
	mStartParselets[Token::Identifier] = new ValueParselet;
	mStartParselets[Token::NumberLiteral] = new NumberParselet;
	mStartParselets[Token::OpenSquareBracket] = new TupleParselet;
}

Parser::~Parser() {
	for (StartParselet* parselet : mStartParselets)
		delete parselet;
}

void Parser::parseStatement() {
	if (mCurrentTokens.isEmpty())
		return;

	Token first = mCurrentTokens.first();
	mCurrentTokens.removeFirst();

	if (first.type == Token::Keyword) {
		if (first.data.toInt() == KeywordOrg) {
			if (mCurrentTokens.size() != 1)
				emit parseError("Called org without/with too many argument(s)");
			else {
				AExpression* exp = parseExpression();

				if (exp)
					emit statementReady(new OrgStatement(exp, returnParent()));
				else
					emit parseError("Invalid org expression");
			}
		}
	} else if (first.type == Token::Identifier) {
		QList<AExpression*> arguments;

		while (AExpression* exp = parseExpression())
			arguments.append(exp);

		QString codeName = first.data.toString();
		const CodeTemplate& codeTemplate = mTemplateLibrary->findTemplate(codeName, arguments.size());

		if (codeTemplate.isValid())
			emit statementReady(new CodeStatement(&codeTemplate, arguments, returnParent()));
		else {
			if (!mTemplateLibrary->findTemplate(first.data.toString()).isValid())
				emit parseError("Invalid code identifier: " % codeName);
			else
				emit parseError("Invalid argument count for: " % codeName);
		}
	} else
		emit parseError("Unexpected token: " % first.data.toString());

	mCurrentTokens.clear();
}

void Parser::parseLabel() {
	if (mCurrentTokens.size() != 1)
		emit parseError("Tried to define label with no/multiple tokens");
	else {
		Token token = mCurrentTokens.at(0);

		if (token.type == Token::Identifier)
			emit statementReady(new LabelStatement(token.data.toString(), returnParent()));
		else
			emit parseError("Tried to define label with not an identifier: " % token.data.toString());
	}

	mCurrentTokens.clear();
}

QObject* Parser::returnParent() {
	QObject* thisParent = parent();

	if (thisParent)
		return thisParent;

	return this;
}

AExpression* Parser::parseExpression(int precedence) {
	StartParselet* startParselet = nullptr;

	if (!(startParselet = mStartParselets.value(peekNext().type, nullptr)))
		return nullptr;

	AExpression* expression = startParselet->parseExpression(removeNext(), this);

	NextParselet* nextParselet = nullptr;

	while ((nextParselet = mNextParselets.value(peekNext().type, nullptr)) &&
		   (nextParselet->precedence() > precedence))
		expression = nextParselet->parseExpression(expression, removeNext(), this);

	return expression;
}

Token Parser::peekNext() const {
	if (mCurrentTokens.isEmpty())
		return { Token::Undefined, QVariant() };
	return mCurrentTokens.first();
}

Token Parser::removeNext() {
	if (mCurrentTokens.isEmpty())
		return { Token::Undefined, QVariant() };

	Token token = mCurrentTokens.first();
	mCurrentTokens.removeFirst();

	return token;
}

bool Parser::removeNext(Token::TokenType type) {
	if (mCurrentTokens.isEmpty())
		return false;

	if (mCurrentTokens.first().type != type)
		return false;

	mCurrentTokens.removeFirst();
	return true;
}

bool Parser::checkNext(Token::TokenType type) const {
	if (mCurrentTokens.isEmpty())
		return false;
	return (mCurrentTokens.first().type == type);
}

void Parser::handleToken(Token token) {
	if (token.type == Token::LineBreak) {
		parseStatement();
	} else if (token.type == Token::Colon) {
		parseLabel();
	} else if (token.type == Token::StringLiteral) {
		emit parseError("String literals have no meaning yet, sorry :(");
	} else
		mCurrentTokens.append(token);
}

} // namespace tea
