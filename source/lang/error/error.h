#ifndef TEA_ERROR_H
#define TEA_ERROR_H

#include "lang/core/fileposition.h"

namespace tea {

class Error {
public:
	enum Scope {
		CodeProcessing,
		ValueProcessing,

		Preprocessing,
		Lexing,
		Parsing,

		Assembling,
		Disassembling
	};

public:
	Error(Scope when, FilePosition where, QString what);

private:
	Scope mWhen;
	FilePosition mWhere;
	QString mWhat;
};

} // namespace tea

#endif // TEA_ERROR_H
