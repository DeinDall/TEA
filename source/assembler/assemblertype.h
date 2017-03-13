#ifndef TEA_ASSEMBLERTYPE_H
#define TEA_ASSEMBLERTYPE_H

#include <QVariant>

namespace tea {

struct AssemblerType {
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

#endif // TEA_ASSEMBLERTYPE_H
