#include "preprocessor.h"

#include <QFile>
#include <QTextStream>

namespace tea {

Preprocessor::Preprocessor()
	: mCurrentIncludeDepth(0) {}

void Preprocessor::processLine(QString line) {
	emit lineReady(line);
}

void Preprocessor::handleFile(QString fileName) {
	if (mCurrentIncludeDepth > 100) // TODO: put that constant somewhere
		emit error("Maximum Include depth reached, make sure you have no looping inclusions");

	// TODO: maybe not process the file while it is open?

	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
		return; // TODO: emit error();

	++mCurrentIncludeDepth;
	QTextStream stream(&file);

	while (!stream.atEnd())
		processLine(stream.readLine());

	file.close();

	if ((--mCurrentIncludeDepth) == 0)
		emit finished();
}

} // namespace tea
