#include "lexerexception.h"

namespace tea {

LexerException::LexerException(QString what, FilePosition where)
	: mWhat(what), mWhere(where) {}

QString LexerException::what() const {
	return mWhat;
}

const FilePosition& LexerException::where() const {
	return mWhere;
}

} // namespace tea
