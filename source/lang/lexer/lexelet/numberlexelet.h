#ifndef TEA_NUMBERLEXELET_H
#define TEA_NUMBERLEXELET_H

#include "abstractlexelet.h"

namespace tea {

class NumberLexelet : public AbstractLexelet {
public:
	NumberLexelet();

	Token tokenize(QStringRef& stringReference, FilePosition filePosition) const;
};

} // namespace tea

#endif // TEA_NUMBERLEXELET_H
