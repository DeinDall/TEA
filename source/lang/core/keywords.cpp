#include "keywords.h"

namespace tea {

Keyword getKeywordFor(QStringRef ref) {
	if (ref == "org")
		return KeywordOrg;
	return KeywordUndefined;
}

QString getKeywordIdentifier(int keyword) {
	if (keyword == KeywordOrg)
		return "org";
	return "";
}

} // namespace tea
