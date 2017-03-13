#ifndef TEA_ROMREF_H
#define TEA_ROMREF_H

#include "rom.h"

namespace tea {

class ROMRef {
	friend class ROM;
public:
	using const_iterator = ROM::const_iterator;

public:
	ROMRef();

	inline const ROM* romPtr() const { return mROM; }
	inline bool isNull() const { return (mROM); }

	char at(uint position) const;

	uint offset() const;
	uint size() const;

	inline const_iterator begin() const { return mROM->begin() + mOffset; }
	inline const_iterator end() const { return mROM->begin() + mOffset + mSize; }

	ROMRef mid(uint pos) const;
	ROMRef mid(uint pos, uint size) const;
	ROMRef left(uint size) const;
	ROMRef right(uint size) const;

protected:
	ROMRef(const ROM* rom, uint offset, uint size);

private:
	const ROM* mROM;
	uint mOffset, mSize;
};

} // namespace tea

#endif // TEA_ROMREF_H
