#include "romutil.h"

namespace tea {

quint64 readNumber(ROMRef::const_iterator begin, ROMRef::const_iterator end) {
	quint64 result = 0;

	for (int i=0; i<(end - begin); ++i)
		result |= (((*(begin+i)) & 0xFF) << (8*i));

	return result;
}

namespace snes {

bool isLoRomPointer(uint pointer) {
	return (pointer & 0x8000);
}

uint offsetFromLoRomPointer(uint pointer) {
	return (((pointer >> 16) & 0x7F) << 15) | (pointer & 0x7FFF);
}

uint loRomPointerFromOffset(uint offset) {
	return ((offset >> 15) << 16) | (offset & 0x7FFF) | 0x808000;
}

} // namespace snes

namespace gba {

uint offsetFromPointer(uint pointer) {
	return (pointer & 0x7FFFFFFF);
}

uint pointerFromOffset(uint offset) {
	return (offset | 0x80000000);
}

}

} // namespace tea
