#ifndef TEA_VALUEPARSELET_H
#define TEA_VALUEPARSELET_H

#include "startparselet.h"

namespace tea {

class ValueParselet : public StartParselet {
public:
	ValueParselet();
	AExpression* parseExpression(Token token, Parser* parser) const;
};

} // namespace tea

#endif // TEA_VALUEPARSELET_H
