#ifndef TEA_GENERATEDSTRINGSOURCE_H
#define TEA_GENERATEDSTRINGSOURCE_H

#include "istringsource.h"

namespace tea {

class GeneratedStringSource : public IStringSource {
public:
	GeneratedStringSource(QString source);

	QString readString(int position, int length) const;

private:
	QString mData;
};

} // namespace tea

#endif // TEA_GENERATEDSTRINGSOURCE_H
