#include "parser.h"

#include <QStringBuilder>

#include "lang/core/keywords.h"

#include "lang/core/expression/numberexpression.h"
#include "lang/core/expression/valueexpression.h"
#include "lang/core/expression/tupleexpression.h"

#include "lang/core/statement/codestatement.h"
#include "lang/core/statement/labelstatement.h"
#include "lang/core/statement/orgstatement.h"

namespace tea {

Parser::Parser(const CodeTemplateLibrary* lib, QObject* parent)
	: QObject(parent), mTemplateLibrary(lib) {}

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
				AbstractExpression* exp = parseExpression();

				if (exp)
					emit statementReady(new OrgStatement(exp, returnParent()));
				else
					emit parseError("Invalid org expression");
			}
		}
	} else if (first.type == Token::Identifier) {
		QList<AbstractExpression*> arguments;

		while (AbstractExpression* exp = parseExpression())
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

AbstractExpression* Parser::parseExpression() {
	if (checkNext(Token::OpenSquareBracket)) {
		mCurrentTokens.removeFirst();

		QList<AbstractExpression*> tupleExpressions;

		while (!checkNext(Token::CloseSquareBracket)) {
			tupleExpressions.append(parseExpression());
			if (!checkNext(Token::Comma))
				break;
			mCurrentTokens.removeFirst();
		}

		if (!checkNext(Token::CloseSquareBracket)) {
			if (mCurrentTokens.isEmpty())
				emit parseError("Tuple not closed (missing \']\')");
			else
				emit parseError("Unexpected token " % mCurrentTokens.first().toString());
		} else {
			mCurrentTokens.removeFirst();

			return new TupleExpression(tupleExpressions, returnParent());
		}
	} else if (checkNext(Token::NumberLiteral)) {
		quint64 value = mCurrentTokens.first().data.toLongLong();
		mCurrentTokens.removeFirst();

		return new NumberExpression(value, returnParent());
	} else if (checkNext(Token::Identifier)) {
		QString name = mCurrentTokens.first().data.toString();
		mCurrentTokens.removeFirst();

		return new ValueExpression(name, returnParent());
	}

	return nullptr;
}

AbstractExpression* Parser::parseNext(AbstractExpression* previous, int precedence) {
	if (mCurrentTokens.isEmpty())
		return nullptr;

	Token token = mCurrentTokens.first();
	mCurrentTokens.removeFirst();

	return nullptr;
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
