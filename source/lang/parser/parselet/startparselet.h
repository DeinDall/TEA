#ifndef TEA_STARTPARSELET_H
#define TEA_STARTPARSELET_H

#include "lang/core/expression/abstractexpression.h"

namespace tea {

class Parser;

class StartParselet {
public:
	virtual ~StartParselet();
	virtual AbstractExpression* parseExpression(Token token, Parser* parser) const = 0;
};

} // namespace tea

#endif // TEA_STARTPARSELET_H
