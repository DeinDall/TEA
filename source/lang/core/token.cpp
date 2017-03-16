#include "token.h"

#include <QStringBuilder>

#include "keywords.h"

namespace tea {

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
