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
		emit error(AssemblyException(AssemblyException::Error, AssemblyException::Preprocessing, "Maximum Include depth reached, make sure you have no looping inclusions"));

	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly)) {
		emit error(AssemblyException(AssemblyException::Error, AssemblyException::Preprocessing, "Error while opening file"));
		return;
	}

	QTextStream stream(&file);
	QStringList lines;

	while (!stream.atEnd())
		lines.append(stream.readLine());

	file.close();

	++mCurrentIncludeDepth;

	QString lastFile = mCurrentFile;
	mCurrentFile = fileName;

	for (QString& line : lines)
		processLine(line);

	mCurrentFile = lastFile;

	if ((--mCurrentIncludeDepth) == 0)
		emit finished();
}

} // namespace tea
