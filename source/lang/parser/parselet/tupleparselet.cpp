#include "tupleparselet.h"

#include "lang/parser/parser.h"

#include "lang/core/expression/tupleexpression.h"

namespace tea {

TupleParselet::TupleParselet() {}

AExpression* TupleParselet::parseExpression(Token token, Parser* parser) const {
	if (token.type == Token::OpenSquareBracket) {
		QList<AExpression*> parameters;

		while (!parser->checkNext(Token::CloseSquareBracket)) {
			parameters.append(parser->parseExpression());
			if (!parser->removeNext(Token::Comma))
				break;
		}

		if (!parser->removeNext(Token::CloseSquareBracket))
			return nullptr;
		else
			return new TupleExpression(parameters, parser);
	}

	return nullptr;
}

} // namespace tea
