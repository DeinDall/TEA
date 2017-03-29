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

bool Parser::TokenQueue::checkNext(Token::TokenType type) const {
	if (mTokens.isEmpty())
		return false;
	return (mTokens.head().type == type);
}

Token Parser::TokenQueue::peekNext() const {
	if (mTokens.isEmpty())
		return { Token::Undefined, QVariant() };
	return mTokens.head();
}

Token Parser::TokenQueue::removeNext() {
	if (mTokens.isEmpty())
		return { Token::Undefined, QVariant() };
	return mTokens.dequeue();
}

bool Parser::TokenQueue::removeNext(Token::TokenType type) {
	if (mTokens.isEmpty())
		return false;

	if (mTokens.head().type != type)
		return false;

	mTokens.dequeue();
	return true;
}

Parser::Parser(const CodeLibrary* lib, QObject* parent)
	: QObject(parent), mErrored(false), mCodeLibrary(lib) {
	mStartParselets[Token::Identifier] = new ValueParselet;
	mStartParselets[Token::NumberLiteral] = new NumberParselet;
	mStartParselets[Token::OpenSquareBracket] = new TupleParselet;
}

Parser::~Parser() {
	for (StartParselet* parselet : mStartParselets)
		delete parselet;

	for (NextParselet* parselet : mNextParselets)
		delete parselet;
}

Parser::TokenQueue& Parser::tokens() {
	return mTokenQueue;
}

void Parser::setCodeLibrary(const CodeLibrary* lib) {
	mCodeLibrary = lib;
}

void Parser::parseStatement() {
	if (mTokenQueue.mTokens.isEmpty())
		return;

	Token first = mTokenQueue.removeNext();

	if (first.type == Token::Keyword) {
		if (first.data.toInt() == KeywordOrg) {
			QList<AbstractExpression*> arguments = parseArguments();

			if (arguments.size() != 1)
				throw AssemblyException(AssemblyException::Error, AssemblyException::Parsing, "Invalid argument count for org");
			else
				emit statementReady(new OrgStatement(arguments.at(0), this));
		}
	} else if (first.type == Token::Identifier) {
		QList<AbstractExpression*> arguments = parseArguments();
		QString codeName = first.data.toString();

		const CodeTemplate* codeTemplate = mCodeLibrary->findCodeTemplate(codeName, arguments.size());

		if (codeTemplate)
			emit statementReady(new CodeStatement(codeTemplate, arguments, this));
		else {
			if (!mCodeLibrary->findCodeTemplate(codeName))
				throw AssemblyException(AssemblyException::Error, AssemblyException::Parsing, "Invalid code identifier: " % codeName);
			else
				throw AssemblyException(AssemblyException::Error, AssemblyException::Parsing, "Invalid argument count for: " % codeName);
		}
	} else
		throw AssemblyException(AssemblyException::Error, AssemblyException::Parsing, "Unexpected token: " % first.data.toString());

	mTokenQueue.mTokens.clear();
}

void Parser::parseLabel() {
	if (mTokenQueue.mTokens.size() != 1)
		throw AssemblyException(AssemblyException::Error, AssemblyException::Parsing, "Tried to define label with no/multiple tokens");
	else {
		Token token = mTokenQueue.mTokens.dequeue();

		if (token.type == Token::Identifier)
			emit statementReady(new LabelStatement(token.data.toString(), this));
		else
			throw AssemblyException(AssemblyException::Error, AssemblyException::Parsing, "Tried to define label with not an identifier: " % token.data.toString());
	}

	mTokenQueue.mTokens.clear();
}

AbstractExpression* Parser::parseExpression(int precedence) {
	StartParselet* startParselet = nullptr;

	if (!(startParselet = mStartParselets.value(mTokenQueue.peekNext().type, nullptr)))
		return nullptr;

	AbstractExpression* expression = startParselet->parseExpression(mTokenQueue.removeNext(), this);

	NextParselet* nextParselet = nullptr;

	while ((nextParselet = mNextParselets.value(mTokenQueue.peekNext().type, nullptr)) &&
		   (nextParselet->precedence() > precedence))
		expression = nextParselet->parseExpression(expression, mTokenQueue.removeNext(), this);

	return expression;
}

QList<AbstractExpression*> Parser::parseArguments() {
	QList<AbstractExpression*> result;

	while (AbstractExpression* exp = parseExpression())
		result.append(exp);

	return result;
}

void Parser::handleToken(tea::Token token) {
	if (mErrored)
		return;

	try {
		if (token.type == Token::LineBreak) {
			parseStatement();
		} else if (token.type == Token::Colon) {
			parseLabel();
		} else if (token.type == Token::StringLiteral) {
			throw AssemblyException(AssemblyException::Error, AssemblyException::Parsing, "String literals have no meaning yet, sorry :(");
		} else
			mTokenQueue.mTokens.enqueue(token);
	} catch (const AssemblyException& exception) {
		emit error(exception);
		mErrored = true;
	}
}

void Parser::finishParsing() {
	if (mErrored)
		return;

	try {
		parseStatement();
		emit finished();
	} catch (const AssemblyException& exception) {
		emit error(exception);
		mErrored = true;
	}
}

} // namespace tea
