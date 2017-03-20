#include "tupleparselet.h"

#include "lang/parser/parser.h"

#include "lang/core/expression/tupleexpression.h"

namespace tea {

TupleParselet::TupleParselet() {}

AbstractExpression* TupleParselet::parseExpression(Token token, Parser* parser) const {
	if (token.type == Token::OpenSquareBracket) {
		QList<AbstractExpression*> parameters;

		while (!parser->tokens().checkNext(Token::CloseSquareBracket)) {
			parameters.append(parser->parseExpression());
			if (!parser->tokens().removeNext(Token::Comma))
				break;
		}

		if (!parser->tokens().removeNext(Token::CloseSquareBracket))
			return nullptr;
		else
			return new TupleExpression(parameters, parser);
	}

	return nullptr;
}

} // namespace tea
