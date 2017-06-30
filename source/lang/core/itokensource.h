#ifndef TEA_ITOKENSOURCE_H
#define TEA_ITOKENSOURCE_H

#include "token.h"

namespace tea {

class ITokenSource {
public:
	virtual inline ~ITokenSource() {}

	virtual Token peekToken() = 0;
	virtual Token nextToken() = 0;

	inline bool tokenMatches(Token::TokenType type) { return peekToken().type == type; }
};

} // namespace tea

#endif // TEA_ITOKENSOURCE_H
