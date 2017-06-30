#ifndef TEA_ISTRINGSOURCE_H
#define TEA_ISTRINGSOURCE_H

#include <QString>

namespace tea {

class IStringSource {
public:
	virtual inline ~IStringSource() {}
	virtual QString readString(int position, int length) const = 0;
};

} // namespace tea

#endif // TEA_ISTRINGSOURCE_H
