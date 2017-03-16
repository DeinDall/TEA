#ifndef TEA_ROMWRITER_H
#define TEA_ROMWRITER_H

#include "rom.h"

namespace tea {

class ROMWriter {
public:
	ROMWriter(const ROM* rom);

	const ROM* romPtr() const;

	void writeAt(uint pos, char val);
	void writeAt(uint pos, QByteArray data);
	void writeBits(quint64 bitOffset, quint64 bitSize, quint64 value);

	void outputToFile(QString fileName) const;

private:
	const ROM* mROM;
	QByteArray mXORArray;
};

} // namespace tea

#endif // TEA_ROMWRITER_H
