#include "romref.h"

namespace tea {

ROMRef::ROMRef()
	: mROM(nullptr), mOffset(0), mSize(0) {}

ROMRef::ROMRef(const ROM* rom, uint offset, uint size)
	: mROM(rom), mOffset(offset), mSize(size) {}

char ROMRef::at(uint position) const {
	if (mROM)
		if (position < mSize)
			return mROM->at(mOffset+position);
	return 0;
}

uint ROMRef::offset() const {
	return mOffset;
}

uint ROMRef::size() const {
	return mSize;
}

ROMRef ROMRef::mid(uint pos) const {
	return mid(pos, mSize - pos);
}

ROMRef ROMRef::mid(uint pos, uint size) const {
	if (pos > mSize)
		pos = mSize;
	if ((size + pos) > mSize)
		size = mSize - pos;
	return ROMRef(mROM, mOffset + pos, size);
}

ROMRef ROMRef::left(uint size) const {
	return mid(0, size);
}

ROMRef ROMRef::right(uint size) const {
	return mid(mSize - size);
}

} // namespace tea
