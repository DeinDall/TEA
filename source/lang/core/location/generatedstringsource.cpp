#include "generatedstringsource.h"

namespace tea {

GeneratedStringSource::GeneratedStringSource(QString source)
	: mData(source) {}

QString GeneratedStringSource::readString(int position, int length) const {
	return mData.mid(position, length);
}

} // namespace tea
