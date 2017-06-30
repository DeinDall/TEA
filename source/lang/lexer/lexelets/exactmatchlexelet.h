#ifndef TEA_EXACTMATCHLEXELET_H
#define TEA_EXACTMATCHLEXELET_H

#include "ilexelet.h"

namespace tea {

template<Token::TokenType TT, int matchSize>
class ExactMatchLexelet : public ILexelet {
public:
	ExactMatchLexelet();

	Token tokenize(QStringRef& stringReference) const {
		stringReference = stringReference.mid(matchSize);
		return Token(TT);
	}
};

} // namespace tea

#endif // TEA_EXACTMATCHLEXELET_H
