#include "keywords.h"

namespace tea {

Keyword getKeywordFor(QStringRef ref) {
	if (ref == "org")
		return KeywordOrg;
	return KeywordUndefined;
}

} // namespace tea
