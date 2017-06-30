#ifndef TEA_ISTRINGSOURCE_H
#define TEA_ISTRINGSOURCE_H

#include <QString>

namespace tea {

class IStringSource {
public:
	virtual inline ~IStringSource() {}

	virtual QString peekString() = 0;
	virtual QString nextString() = 0;

	inline bool atEnd() { return peekString().isNull(); }
};

} // namespace tea

#endif // TEA_ISTRINGSOURCE_H
