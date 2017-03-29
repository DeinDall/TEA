#ifndef TEA_LEXEREXCEPTION_H
#define TEA_LEXEREXCEPTION_H

#include "lang/core/fileposition.h"

#include <QString>

namespace tea {

class LexerException {
public:
	LexerException(QString what, FilePosition where);

	QString what() const;
	const FilePosition& where() const;

private:
	QString mWhat;
	FilePosition mWhere;
};

} // namespace tea

#endif // TEA_LEXEREXCEPTION_H
