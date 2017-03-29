#include "lexer.h"

#include "lang/core/keywords.h"

#include <QDebug>
#include <QStringBuilder>

namespace tea {

Lexer::Lexer(QObject* parent)
	: QObject(parent), mErrored(false) {}

QStringRef Lexer::tokenize(QStringRef ref) {
	if (ref.isEmpty())
		return ref;

	QChar chr = ref.at(0);

	if (chr.isSpace())
		return tokenizeSpace(ref);
	else if (chr.isNumber())
		return tokenizeNumber(ref);
	else if (chr.isLetter())
		return tokenizeIdentifier(ref);
	else if (chr == '\"')
		return tokenizeString(ref);
	else
		return tokenizeSymbol(ref);
}

QStringRef Lexer::tokenizeSpace(QStringRef ref) {
	int pos = 0;
	QChar chr;

	while (pos < ref.size() && (chr = ref.at(pos)).isSpace()) {
		if (chr == '\n')
			emit tokenReady({ Token::LineBreak, QVariant() });
		++pos;
	}

	return ref.mid(pos);
}

QStringRef Lexer::tokenizeNumber(QStringRef ref) {
	int pos = 0;
	QChar chr;

	while (pos < ref.size() && (chr = ref.at(pos)).isLetterOrNumber())
		++pos;

	bool ok = false;
	qint64 value = ref.left(pos).toLongLong(&ok, 0);

	if (!ok)
		throw AssemblyException(AssemblyException::Error, AssemblyException::Lexing, "Unable to parse number");
	else {
		emit tokenReady({ Token::NumberLiteral, QVariant(value) });
		return ref.mid(pos);
	}
}

QStringRef Lexer::tokenizeIdentifier(QStringRef ref) {
	int pos = 0;
	QChar chr;

	while (pos < ref.size() && (chr = ref.at(pos)).isLetterOrNumber())
		++pos;

	QStringRef stringRef(ref.left(pos));

	int keyword = keywordIndex(stringRef);

	if (keyword != KeywordUndefined)
		emit tokenReady({ Token::Keyword, QVariant(keyword) });
	else
		emit tokenReady({ Token::Identifier, QVariant(stringRef.toString()) });

	return ref.mid(pos);
}

QStringRef Lexer::tokenizeString(QStringRef ref) {
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

	return ref.mid(pos);
}

QStringRef Lexer::tokenizeSymbol(QStringRef ref) {
	if (ref.at(0) == ':')
		emit tokenReady({ Token::Colon, QVariant() });
	else if (ref.at(0) == '[')
		emit tokenReady({ Token::OpenSquareBracket, QVariant() });
	else if (ref.at(0) == ']')
		emit tokenReady({ Token::CloseSquareBracket, QVariant() });
	else if (ref.at(0) == ',')
		emit tokenReady({ Token::Comma, QVariant() });
	else
		throw AssemblyException(AssemblyException::Error, AssemblyException::Lexing, "Unreckognized token");

	return ref.mid(1);
}

void Lexer::handleLine(QString line) {
	if (mErrored)
		return;

	try {
		QStringRef ref = line.midRef(0);

		while (!ref.isEmpty())
			ref = tokenize(ref);
	} catch (const AssemblyException& exception) {
		emit error(exception);
		mErrored = true;
	}

	emit tokenReady({ Token::LineBreak, QVariant()});
}

void Lexer::finishLexing() {
	emit finished();
}

void Lexer::onError() {
	mErrored = true;
}

} // namespace tea
