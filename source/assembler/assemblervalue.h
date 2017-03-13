#ifndef TEA_ASSEMBLERVALUE_H
#define TEA_ASSEMBLERVALUE_H

#include <QVariant>

namespace tea {

struct AssemblerValue {
	enum TypeEnum {
		NullType,

		Value,
		Number,
		Data
	};

	TypeEnum type;
	QVariant data;
};

} // namespace tea

#endif // TEA_ASSEMBLERVALUE_H
