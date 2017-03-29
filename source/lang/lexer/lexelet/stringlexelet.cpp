#include "stringlexelet.h"

namespace tea {

StringLexelet::StringLexelet() {}

Token StringLexelet::tokenize(QStringRef& stringReference, FilePosition filePosition) const {
	int pos = 1;
	bool skip = false;
	QChar chr;

	QString stringValue;
	stringValue.reserve(stringReference.size());

	while (pos < stringReference.size() && (skip || ((chr = stringReference.at(pos)) != '\"'))) {
		if (chr == '\\')
			skip = true;
		else if (skip) {
			if (chr == 't')
				stringValue.append('\t');
			else if (chr == 'n')
				stringValue.append('\n');
			else
				stringValue.append(chr);
			skip = false;
		} else
			stringValue.append(chr);

		++pos;
	}

	stringReference = stringReference.mid(pos);

	return Token(Token::StringLiteral, QVariant(stringValue), filePosition);
}

} // namespace tea
