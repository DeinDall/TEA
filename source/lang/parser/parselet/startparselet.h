#ifndef TEA_STARTPARSELET_H
#define TEA_STARTPARSELET_H

#include "lang/core/expression/aexpression.h"

namespace tea {

class Parser;

class StartParselet {
public:
	virtual ~StartParselet();
	virtual AExpression* parseExpression(Token token, Parser* parser) const = 0;
};

} // namespace tea

#endif // TEA_STARTPARSELET_H
