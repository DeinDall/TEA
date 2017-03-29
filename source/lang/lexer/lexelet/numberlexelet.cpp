#include "numberlexelet.h"

#include "lang/lexer/lexerexception.h"

namespace tea {

NumberLexelet::NumberLexelet() {}

Token NumberLexelet::tokenize(QStringRef& stringReference, FilePosition filePosition) const {
	int pos = 0;

	while (pos < stringReference.size() && stringReference.at(pos).isLetterOrNumber())
		++pos;

	bool ok = false;
	qint64 value = stringReference.left(pos).toLongLong(&ok, 0);

	stringReference = stringReference.mid(pos);

	if (!ok)
		throw LexerException("Error while lexing Number", filePosition);

	return Token(Token::NumberLiteral, QVariant(value), filePosition);
}

} // namespace tea
