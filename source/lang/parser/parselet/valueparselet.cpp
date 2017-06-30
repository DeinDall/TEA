#include "valueparselet.h"

#include "lang/parser/parser.h"

#include "lang/core/expression/valueexpression.h"

namespace tea {

ValueParselet::ValueParselet() {}

AExpression* ValueParselet::parseExpression(Token token, Parser* parser) const {
	if (token.type == Token::Identifier)
		return new ValueExpression(token.data.toString(), parser);
	return nullptr;
}

} // namespace tea
