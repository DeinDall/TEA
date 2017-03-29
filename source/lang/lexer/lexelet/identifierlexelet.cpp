#include "identifierlexelet.h"

#include "lang/core/keywords.h"

namespace tea {

IdentifierLexelet::IdentifierLexelet() {}

Token IdentifierLexelet::tokenize(QStringRef& stringReference, FilePosition filePosition) const {
	int pos = 0;

	while (pos < stringReference.size() && stringReference.at(pos).isLetterOrNumber())
		++pos;

	QStringRef idString(stringReference.left(pos));

	stringReference = stringReference.mid(pos);

	int keyword = keywordIndex(idString);
	if (keyword != KeywordUndefined)
		return Token(Token::Keyword, QVariant(keyword), filePosition);

	return Token(Token::Identifier, QVariant(idString.toString()), filePosition);
}

} // namespace tea
