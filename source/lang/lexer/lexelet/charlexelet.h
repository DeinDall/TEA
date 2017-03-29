#ifndef TEA_CHARLEXELET_H
#define TEA_CHARLEXELET_H

#include "abstractlexelet.h"

namespace tea {

template<Token::Type TT>
class CharLexelet : public AbstractLexelet {
public:
	CharLexelet() {}

	Token tokenize(QStringRef& stringReference, FilePosition filePosition) const {
		stringReference = stringReference.mid(1);
		return Token(TT, filePosition);
	}
};

} // namespace tea

#endif // TEA_CHARLEXELET_H
