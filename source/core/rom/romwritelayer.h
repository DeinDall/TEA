#ifndef TEA_ROMWRITELAYER_H
#define TEA_ROMWRITELAYER_H

#include "rom.h"

namespace tea {

class ROMWriteLayer {
public:
	ROMWriteLayer(const ROM* rom);

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

#endif // TEA_ROMWRITELAYER_H
