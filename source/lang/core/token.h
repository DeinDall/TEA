#ifndef TEA_TOKEN_H
#define TEA_TOKEN_H

#include <QVariant>

namespace tea {

struct Token {
	enum TokenType {
		Undefined = -1,

		Keyword,
		Identifier,
		NumberLiteral,
		StringLiteral,

		LineBreak,
		Colon
	};

	TokenType type;
	QVariant data;

	QString toString() const;
};

} // namespace tea

#endif // TEA_TOKEN_H
