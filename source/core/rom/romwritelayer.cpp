#include "romwritelayer.h"

#include <QFile>

namespace tea {

ROMWriteLayer::ROMWriteLayer(const ROM* rom)
	: mROM(rom) {
	if (mROM)
		mXORArray.fill(0x00, mROM->size());
}

void ROMWriteLayer::writeAt(uint pos, char val) {
	if (pos >= mROM->size())
		return;
	mXORArray[pos] = (mROM->at(pos) ^ val);
}

void ROMWriteLayer::writeAt(uint pos, QByteArray data) {
	if (pos + data.size() >= mROM->size())
		return;

	auto romIt = (mROM->begin() + pos);
	auto xorIt = (mXORArray.begin() + pos);
	auto dataIt = data.cbegin();

	while (dataIt != data.cend())
		(*xorIt++) = (*romIt++) ^ (*dataIt++);
}

void ROMWriteLayer::writeBits(quint64 bitOffset, quint64 bitSize, quint64 value) {
	value <<= (bitOffset & 0x7);
	quint64 mask = ((0x1 << bitSize)-1) << (bitOffset & 0x7);

	for (uint i=(bitOffset >> 3); i<((bitOffset+bitSize+7) >> 3); ++i) {
		char leftoverByte = ((mXORArray[i]) ^ (mROM->at(i))) & (~(mask & 0xFF));
		mXORArray[i] = (mROM->at(i) ^ (leftoverByte | (value & mask & 0xFF)));

		mask >>= 8;
		value >>= 8;
	}
}

void ROMWriteLayer::outputToFile(QString fileName) const {
	QByteArray output;
	output.reserve(mROM->size());

	auto romIt = mROM->begin();
	auto xorIt = mXORArray.cbegin();

	while (xorIt != mXORArray.cend())
		output.append((*xorIt++) ^ (*romIt++));

	QFile file(fileName);

	if (!file.open(QIODevice::WriteOnly))
		return;

	file.write(output);
	file.close();
}

} // namespace tea
