#include "filestringsource.h"

#include <QFile>

namespace tea {

FileStringSource::FileStringSource(QString fileName)
	: mFileName(fileName) {}

QString FileStringSource::readString(int position, int length) const {
	QFile file(mFileName);

	if (!file.open(QIODevice::ReadOnly))
		return "[ERROR WHILE READING FROM FILE]";

	file.seek(position);
	QString result(file.read(length));

	file.close();

	return result;
}

} // namespace tea
