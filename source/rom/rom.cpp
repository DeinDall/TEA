#include "rom.h"
#include "romref.h"

#include <QFile>

namespace tea {

ROM::ROM() {
}

void ROM::loadFromFile(QString fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
		return;

	mFileName = fileName;
	mData = file.readAll();

	file.close();
}

char ROM::at(uint position) const {
	return mData.at(position);
}

uint ROM::size() const {
	return mData.size();
}

ROMRef ROM::ref() const {
	return ROMRef(this, 0, mData.size());
}

ROMRef ROM::midRef(uint pos) const {
	return ref().mid(pos);
}

ROMRef ROM::midRef(uint pos, uint size) const {
	return ref().mid(pos, size);
}

ROMRef ROM::leftRef(uint size) const {
	return ref().left(size);
}

ROMRef ROM::rightRef(uint size) const {
	return ref().right(size);
}

} // namespace tea
