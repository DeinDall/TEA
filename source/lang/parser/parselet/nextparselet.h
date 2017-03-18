#ifndef TEA_NEXTPARSELET_H
#define TEA_NEXTPARSELET_H

#include "lang/core/expression/abstractexpression.h"

namespace tea {

class Parser;

class NextParselet {
public:
	virtual ~NextParselet();

	virtual AbstractExpression* parseExpression(AbstractExpression* previous, Token token, Parser* parser) const = 0;
	virtual int precedence() const = 0;
};

} // namespace tea

#endif // TEA_NEXTPARSELET_H
