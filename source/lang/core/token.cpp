#include "token.h"

#include <QStringBuilder>

#include "keywords.h"

namespace tea {

Token::Token() {}

Token::Token(Type aType, const QVariant& aData, const FilePosition& aPosition)
	: type(aType), data(aData), position(aPosition) {}

Token::Token(Type aType, const FilePosition& aPosition)
	: Token(aType, QVariant(), aPosition) {}

QString Token::toString() const {
	switch (type) {
	case Identifier:
		return data.toString();
	case NumberLiteral:
		return ("0x" % QString::number(data.toLongLong(), 16));
	case StringLiteral:
		return ("\"" % data.toString() % "\"");
	case Keyword:
		return keywordIdentifier(data.toInt());
	case Colon:
		return ":";
	case LineBreak:
		return "\n";
	case OpenSquareBracket:
		return "[";
	case CloseSquareBracket:
		return "]";
	case Comma:
		return ",";
	default:
		return "";
	}
}

} // namespace tea
