#include "errorhandler.h"

namespace tea {

ErrorHandler::ErrorHandler() {}

bool ErrorHandler::hasError() const {
	return !mErrorQueue.isEmpty();
}

Error ErrorHandler::nextError() {
	return mErrorQueue.dequeue();
}

void ErrorHandler::notifyError() {
	emit error();
}

} // namespace tea
