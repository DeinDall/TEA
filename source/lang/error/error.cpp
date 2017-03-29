#include "error.h"

namespace tea {

Error::Error(Scope when, FilePosition where, QString what)
	: mWhen(when), mWhere(where), mWhat(what) {}

} // namespace tea
