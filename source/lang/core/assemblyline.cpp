#include "assemblyline.h"

namespace tea {

AssemblyLine::AssemblyLine()
	: lineNumber(0) {}

AssemblyLine::AssemblyLine(QString aLineData, uint aLineNumber, QString aFileName)
	: lineData(aLineData), lineNumber(aLineNumber), fileName(aFileName) {}

FilePosition AssemblyLine::makePosition(uint column) const {
	return FilePosition(fileName, lineNumber, column);
}

} // namespace tea
