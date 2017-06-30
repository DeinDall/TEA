#ifndef TEA_FILESTRINGSOURCE_H
#define TEA_FILESTRINGSOURCE_H

#include "istringsource.h"

namespace tea {

class FileStringSource : public IStringSource {
public:
	FileStringSource(QString fileName);

	QString readString(int position, int length) const;

private:
	QString mFileName;
};

} // namespace tea

#endif // TEA_FILESTRINGSOURCE_H
