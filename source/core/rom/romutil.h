#ifndef TEA_ROMUTIL_H
#define TEA_ROMUTIL_H

#include "romref.h"

namespace tea {

quint64 readNumber(ROMRef::const_iterator begin, ROMRef::const_iterator end);
QByteArray makeNumber(quint64 value, uint size);

namespace snes_lorom {

// returns if the pointer points into the rom (not ram or stuff)
bool isPointer(uint pointer);

uint offsetFromPointer(uint pointer);
uint pointerFromOffset(uint offset);

} // namespace snes

namespace gba {

uint offsetFromPointer(uint pointer);
uint pointerFromOffset(uint offset);

}  // namespace gba

} // namespace tea

#endif // TEA_ROMUTIL_H
