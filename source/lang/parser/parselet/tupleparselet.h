#ifndef TEA_TUPLEPARSELET_H
#define TEA_TUPLEPARSELET_H

#include "startparselet.h"

namespace tea {

class TupleParselet : public StartParselet {
public:
	TupleParselet();
	AbstractExpression* parseExpression(Token token, Parser* parser) const;
};

} // namespace tea

#endif // TEA_TUPLEPARSELET_H
