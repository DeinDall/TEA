#ifndef TEA_NUMBERPARSELET_H
#define TEA_NUMBERPARSELET_H

#include "startparselet.h"

namespace tea {

class NumberParselet : public StartParselet {
public:
	NumberParselet();
	AbstractExpression* parseExpression(Token token, Parser* parser) const;
};

} // namespace tea

#endif // TEA_NUMBERPARSELET_H
