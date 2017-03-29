#ifndef TEA_IDENTIFIERLEXELET_H
#define TEA_IDENTIFIERLEXELET_H

#include "abstractlexelet.h"

namespace tea {

class IdentifierLexelet : public AbstractLexelet {
public:
	IdentifierLexelet();

	Token tokenize(QStringRef& stringReference, FilePosition filePosition) const;
};

} // namespace tea

#endif // TEA_IDENTIFIERLEXELET_H
