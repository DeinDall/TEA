#include "parser.h"

#include "lexer/keywords.h"

#include "lang/expression/codeexpression.h"
#include "lang/expression/numberexpression.h"
#include "lang/expression/valueexpression.h"
#include "lang/expression/labelexpression.h"
#include "lang/expression/orgexpression.h"

#include <QStringBuilder>

namespace tea {

Parser::Parser(const CodeTemplateLibrary* lib, QObject* parent)
	: mTemplateLibrary(lib), QObject(parent) {}

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
				Token token = mCurrentTokens.at(0);

				if (token.type == Token::NumberLiteral) {
					emit expressionReady(new OrgExpression(token.data.toLongLong(), expressionParent()));
				} else
					emit parseError("Called org with a non-number argument");
			}
		}
	} else if (first.type == Token::Identifier) {
		QString codeName = first.data.toString();
		uint argCount = mCurrentTokens.size();

		const CodeTemplate& codeTemplate = mTemplateLibrary->findTemplate(codeName, argCount);

		if (codeTemplate.isValid()) {
			QList<AbstractExpression*> codeArguments;
			codeArguments.reserve(argCount);

			for (int i=0; i<argCount; ++i) {
				if (AbstractExpression* exp = singleTokenExpression(mCurrentTokens.at(i)))
					codeArguments.append(exp);
				else {
					emit parseError("Invalid code argument token: " % mCurrentTokens.at(i).data.toString());
					break;
				}
			}

			if (codeArguments.size() == argCount) // No errors encountered
				emit expressionReady(new CodeExpression(&codeTemplate, codeArguments, expressionParent()));
		} else {
			if (!mTemplateLibrary->findTemplate(first.data.toString()).isValid())
				emit parseError("Invalid code identifier: " % codeName);
			else
				emit parseError("Invalid argument count for: " % codeName);
		}
	} else {
		emit parseError("Unexpected token: " % first.data.toString());
	}

	mCurrentTokens.clear();
}

void Parser::parseLabel() {
	if (mCurrentTokens.size() != 1)
		emit parseError("Tried to define label with no/multiple tokens");
	else {
		Token token = mCurrentTokens.at(0);

		if (token.type == Token::Identifier)
			emit expressionReady(new LabelExpression(token.data.toString(), expressionParent()));
		else
			emit parseError("Tried to define label with not an identifier: " % token.data.toString());
	}

	mCurrentTokens.clear();
}

QObject* Parser::expressionParent() {
	QObject* thisParent = parent();

	if (thisParent)
		return thisParent;

	return this;
}

AbstractExpression* Parser::singleTokenExpression(Token token) {
	if (token.type == Token::NumberLiteral)
		return new NumberExpression(token.data.toLongLong(), NumberExpression::BaseHex, expressionParent());
	else if (token.type == Token::Identifier)
		return new ValueExpression(token.data.toString(), expressionParent());
	return nullptr;
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
