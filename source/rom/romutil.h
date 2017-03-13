#ifndef TEA_ROMUTIL_H
#define TEA_ROMUTIL_H

#include "romref.h"

namespace tea {

quint64 readNumber(ROMRef::const_iterator begin, ROMRef::const_iterator end);

namespace snes {

// returns if the pointer points into the rom (not ram or stuff)
bool isLoRomPointer(uint pointer);

uint offsetFromLoRomPointer(uint pointer);
uint loRomPointerFromOffset(uint offset);

} // namespace snes

namespace gba {

uint offsetFromPointer(uint pointer);
uint pointerFromOffset(uint offset);

}  // namespace gba

} // namespace tea

#endif // TEA_ROMUTIL_H
