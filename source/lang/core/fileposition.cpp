#include "fileposition.h"

namespace tea {

FilePosition::FilePosition()
	: FilePosition("E R R O R ?", 0, 0) {}

FilePosition::FilePosition(QString fname, uint l, uint c)
	: fileName(fname), line(l), column(c) {}

} // namespace tea
