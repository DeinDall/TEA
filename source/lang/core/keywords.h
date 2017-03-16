#ifndef TEA_KEYWORDS_H
#define TEA_KEYWORDS_H

#include <QStringRef>

namespace tea {

enum Keyword {
	KeywordUndefined = 0,
	KeywordOrg
};

Keyword getKeywordFor(QStringRef ref);
QString getKeywordIdentifier(int keyword);

} // namespace tea

#endif // TEA_KEYWORDS_H
