#ifndef TEA_KEYWORDS_H
#define TEA_KEYWORDS_H

#include <QStringRef>

namespace tea {

enum Keyword {
	KeywordUndefined = -1,
	KeywordOrg
};

int keywordIndex(QStringRef ref);
QString keywordIdentifier(int keyword);

} // namespace tea

#endif // TEA_KEYWORDS_H
