#include "romwriter.h"

#include <QFile>

namespace tea {

ROMWriter::ROMWriter(const ROM* rom)
	: mROM(rom) {
	if (mROM)
		mXORArray.fill(0x00, mROM->size());
}

void ROMWriter::writeAt(uint pos, char val) {
	if (pos >= mROM->size())
		return;
	mXORArray[pos] = (mROM->at(pos) ^ val);
}

void ROMWriter::writeAt(uint pos, QByteArray data) {
	if (pos + data.size() >= mROM->size())
		return;

	auto romIt = (mROM->begin() + pos);
	auto xorIt = (mXORArray.begin() + pos);
	auto dataIt = data.cbegin();

	while (dataIt != data.cend())
		(*xorIt++) = (*romIt++) ^ (*dataIt++);
}

void ROMWriter::outputToFile(QString fileName) const {
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
