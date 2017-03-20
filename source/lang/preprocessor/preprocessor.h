#ifndef TEA_PREPROCESSOR_H
#define TEA_PREPROCESSOR_H

#include <QObject>

namespace tea {

class Preprocessor : public QObject {
	Q_OBJECT
public:
	Preprocessor();

	void processLine(QString line);

signals:
	void lineReady(QString line);
	void finished();
	void error(QString what);

public slots:
	void handleFile(QString fileName);

private:
	int mCurrentIncludeDepth;
};

} // namespace tea

#endif // TEA_PREPROCESSOR_H
