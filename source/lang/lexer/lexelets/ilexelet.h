#ifndef TEA_ILEXELET_H
#define TEA_ILEXELET_H

#include "lang/core/token.h"

namespace tea {

class ILexelet {
public:
	ILexelet();

	virtual Token tokenize(QStringRef& stringReference) const = 0;
};

} // namespace tea

#endif // TEA_ILEXELET_H
