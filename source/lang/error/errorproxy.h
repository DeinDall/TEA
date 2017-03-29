#ifndef TEA_ERRORPROXY_H
#define TEA_ERRORPROXY_H

#include "errorhandler.h"

namespace tea {

class ErrorProxy {
public:
	ErrorProxy();

	void registerError(Error::Scope when, FilePosition where, QString what);

private:
	ErrorHandler* mHandler;
};

} // namespace tea

#endif // TEA_ERRORPROXY_H
