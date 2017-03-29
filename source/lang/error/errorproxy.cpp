#include "errorproxy.h"

namespace tea {

ErrorProxy::ErrorProxy() {}

void ErrorProxy::registerError(Error::Scope when, FilePosition where, QString what) {
	mHandler->mReadWriteLock.lockForWrite();
		mHandler->mErrorQueue.enqueue(Error(when, where, what));
		mHandler->notifyError();
	mHandler->mReadWriteLock.unlock();
}

} // namespace tea
