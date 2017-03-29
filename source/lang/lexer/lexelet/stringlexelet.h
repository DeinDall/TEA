#ifndef TEA_STRINGLEXELET_H
#define TEA_STRINGLEXELET_H

#include "abstractlexelet.h"

namespace tea {

class StringLexelet : public AbstractLexelet {
public:
	StringLexelet();

	Token tokenize(QStringRef& stringReference, FilePosition filePosition) const;
};

} // namespace tea

#endif // TEA_STRINGLEXELET_H
