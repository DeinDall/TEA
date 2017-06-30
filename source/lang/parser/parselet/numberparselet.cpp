#include "numberparselet.h"

#include "lang/parser/parser.h"

#include "lang/core/expression/numberexpression.h"

namespace tea {

NumberParselet::NumberParselet() {}

AExpression* NumberParselet::parseExpression(Token token, Parser* parser) const {
	if (token.type == Token::NumberLiteral)
		return new NumberExpression(token.data.toLongLong(), parser);
	return nullptr;
}

} // namespace tea
