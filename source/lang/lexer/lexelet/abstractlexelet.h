#ifndef TEA_ABSTRACTLEXELET_H
#define TEA_ABSTRACTLEXELET_H

#include "lang/core/token.h"

namespace tea {

class AbstractLexelet {
public:
	virtual ~AbstractLexelet();

	virtual Token tokenize(QStringRef& stringReference, FilePosition filePosition) const = 0;
};

} // namespace tea

#endif // TEA_ABSTRACTLEXELET_H
