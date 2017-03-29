#ifndef TEA_ASSEMBLYLINE_H
#define TEA_ASSEMBLYLINE_H

#include "fileposition.h"

namespace tea {

// Haha great wordplay right? ;) ;) ;) ;) ;)

struct AssemblyLine {
	AssemblyLine();
	AssemblyLine(QString aLineData, uint aLineNumber, QString aFileName);

	FilePosition makePosition(uint column) const;

	QString lineData;
	uint lineNumber;
	QString fileName;
};

} // namespace tea

#endif // TEA_ASSEMBLYLINE_H
