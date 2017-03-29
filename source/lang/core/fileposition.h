#ifndef TEA_FILEPOSITION_H
#define TEA_FILEPOSITION_H

#include <QString>

namespace tea {

struct FilePosition {
	FilePosition();
	FilePosition(QString fname, uint l, uint c);

	QString fileName;
	uint line, column;
};

} // namespace tea

#endif // TEA_FILEPOSITION_H
