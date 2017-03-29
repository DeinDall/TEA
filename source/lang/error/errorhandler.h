#ifndef TEA_ERRORHANDLER_H
#define TEA_ERRORHANDLER_H

#include <QObject>

#include <QReadWriteLock>
#include <QQueue>

#include "error.h"

namespace tea {

class ErrorHandler : public QObject {
	Q_OBJECT

	friend class ErrorProxy;
public:
	ErrorHandler();

	bool hasError() const;
	Error nextError();

protected:
	void notifyError();

signals:
	void error();

protected:
	QReadWriteLock mReadWriteLock;

	QQueue<Error> mErrorQueue;
};

} // namespace tea

#endif // TEA_ERRORHANDLER_H
