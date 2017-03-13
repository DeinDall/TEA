#include "lexer.h"

#include <QDebug>
#include <QStringBuilder>

#include "keywords.h"

namespace tea {

Lexer::Lexer() {
	QObject::connect(this, &tokenReady, this, &debugToken);
}

void Lexer::tokenize(QStringRef ref) {
	if (ref.isEmpty())
		return;

	QChar chr = ref.at(0);

	if (chr.isSpace())
		tokenizeSpace(ref);
	else if (chr.isNumber())
		tokenizeNumber(ref);
	else if (chr.isLetter())
		tokenizeIdentifier(ref);
	else if (chr == '\"')
		tokenizeString(ref);
	else
		tokenizeSymbol(ref);
}

void Lexer::tokenizeSpace(QStringRef ref) {
	int pos = 0;
	QChar chr;

	while (pos < ref.size() && (chr = ref.at(pos)).isSpace()) {
		if (chr == '\n')
			emit tokenReady({ Token::LineBreak, QVariant() });
		++pos;
	}

	tokenize(ref.mid(pos));
}

void Lexer::tokenizeNumber(QStringRef ref) {
	int pos = 0;
	QChar chr;

	while (pos < ref.size() && (chr = ref.at(pos)).isLetterOrNumber())
		++pos;

	{
		bool ok = false;
		qint64 value = ref.left(pos).toLongLong(&ok, 0);

		if (!ok)
			emit tokenError(ref.left(pos), "Unable to parse number");
		else {
			emit tokenReady({ Token::NumberLiteral, QVariant(value) });
			tokenize(ref.mid(pos));
		}
	}
}

void Lexer::tokenizeIdentifier(QStringRef ref) {
	int pos = 0;
	QChar chr;

	while (pos < ref.size() && (chr = ref.at(pos)).isLetterOrNumber())
		++pos;

	QStringRef stringRef(ref.left(pos));

	if (Keyword keyword = getKeywordFor(stringRef))
		emit tokenReady({ Token::Keyword, QVariant((int) keyword) });
	else
		emit tokenReady({ Token::Identifier, QVariant(stringRef.toString()) });

	tokenize(ref.mid(pos));
}

void Lexer::tokenizeString(QStringRef ref) {
	int pos = 1;
	bool skip = false;
	QChar chr;

	QString stringValue;
	stringValue.reserve(ref.size());

	while (pos < ref.size() && (skip || ((chr = ref.at(pos)) != '\"'))) {
		if (chr == '\\')
			skip = true;
		else {
			if (skip) {
				if (chr == 't')
					stringValue.append('\t');
				else if (chr == 'n')
					stringValue.append('\n');
				else
					stringValue.append(chr);
				skip = false;
			} else
				stringValue.append(chr);
		}

		++pos;
	}

	emit tokenReady({ Token::StringLiteral, QVariant(stringValue) });

	tokenize(ref.mid(pos));
}

void Lexer::tokenizeSymbol(QStringRef ref) {
	if (ref.at(0) == ':')
		emit tokenReady({ Token::Colon, QVariant() });
	else {
		emit tokenError(ref.left(1), "Unreckognized token");
		return;
	}
	tokenize(ref.mid(1));
}

void Lexer::debugToken(Token token) {
	qDebug() << (QString::number(token.type) % ": " % token.data.toString());
}

} // namespace tea
