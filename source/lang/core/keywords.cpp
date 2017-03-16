#include "keywords.h"

#include <QVector>

namespace tea {

static const QVector<QString> keywords = {
	"org"
};

int keywordIndex(QStringRef ref) {
	for (int i=0; i<keywords.size(); ++i)
		if (ref == keywords[i])
			return i;
	return KeywordUndefined;
}

QString keywordIdentifier(int keyword) {
	if (keyword < keywords.size())
		return keywords[keyword];
	return "undefined";
}

} // namespace tea
