#ifndef TEA_KEYWORDS_H
#define TEA_KEYWORDS_H

#include <QStringRef>

namespace tea {

enum Keyword {
	KeywordUndefined = 0,
	KeywordOrg
};

Keyword getKeywordFor(QStringRef ref);

} // namespace tea

#endif // TEA_KEYWORDS_H
