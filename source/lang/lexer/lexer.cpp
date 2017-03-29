#include "lexer.h"

#include "lexerexception.h"

#include "lexelet/numberlexelet.h"
#include "lexelet/identifierlexelet.h"
#include "lexelet/stringlexelet.h"
#include "lexelet/charlexelet.h"

#include <QDebug>
#include <QStringBuilder>

namespace tea {

static bool numberCheck(QChar chr) {
	return chr.isNumber();
}

static bool identifierCheck(QChar chr) {
	return chr.isLetter();
}

template<char C>
static bool charCheck(QChar chr) {
	return (chr == C);
}

Lexer::Lexer(QObject* parent)
	: QObject(parent), mErrored(false) {
	mLexelets.append({ numberCheck, new NumberLexelet });
	mLexelets.append({ identifierCheck, new IdentifierLexelet });
	mLexelets.append({ charCheck<'\"'>, new StringLexelet });

	mLexelets.append({ charCheck<'['>, new CharLexelet<Token::OpenSquareBracket> });
	mLexelets.append({ charCheck<']'>, new CharLexelet<Token::CloseSquareBracket> });
	mLexelets.append({ charCheck<','>, new CharLexelet<Token::Comma> });
	mLexelets.append({ charCheck<':'>, new CharLexelet<Token::Colon> });
}

QStringRef Lexer::tokenize(QStringRef ref) {
	int pos = 0;
	QChar chr;

	while (pos < ref.size() && (chr = ref.at(pos)).isSpace())
		++pos;
	ref = ref.mid(pos);

	if (ref.isEmpty())
		return ref;

	FilePosition filePos = mCurrentLine.makePosition(ref.position());
	bool lexeletFound = false;

	for (const QPair<charCheckFunc_t, AbstractLexelet*>& pair : mLexelets) {
		if ((*pair.first)(ref.at(0))) {
			Token result = pair.second->tokenize(ref, filePos);
			lexeletFound = true;

			if (result.type == Token::Undefined)
				throw LexerException("Unexpected Lexing Error", filePos);

			emit tokenReady(result);
			break;
		}
	}

	if (!lexeletFound)
		throw LexerException("Unreckognized Token", filePos);

	return ref;
}

void Lexer::handleLine(tea::AssemblyLine line) {
	if (mErrored)
		return;

	try {
		QStringRef ref = line.lineData.midRef(0);

		while (!ref.isEmpty())
			ref = tokenize(ref);

		emit tokenReady(Token(Token::LineBreak, line.makePosition(line.lineData.size())));
	} catch (const LexerException& exception) {
		emit error(AssemblyException(AssemblyException::Error, AssemblyException::Lexing, exception.what()));
		mErrored = true;
	}
}

void Lexer::finishLexing() {
	emit finished();
}

} // namespace tea
