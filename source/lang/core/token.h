#ifndef TEA_TOKEN_H
#define TEA_TOKEN_H

#include <QVariant>

#include "fileposition.h"

namespace tea {

struct Token {
	enum Type {
		Undefined = -1,

		Keyword,
		Identifier,
		NumberLiteral,
		StringLiteral,

		LineBreak,
		Colon,

		OpenSquareBracket,
		CloseSquareBracket,
		Comma
	};

	Token();
	Token(Type aType, const QVariant& aData, const FilePosition& aPosition);
	Token(Type aType, const FilePosition& aPosition);

	QString toString() const;

	Type type;
	QVariant data;

	FilePosition position;
};

} // namespace tea

#endif // TEA_TOKEN_H
