#include "assemblyexception.h"

namespace tea {

AssemblyException::AssemblyException()
	: mLevel(Error), mScope(Assembling) {}

AssemblyException::AssemblyException(ErrorLevel level, ErrorScope scope, QString what)
	: mLevel(level), mScope(scope), mWhat(what) {}

AssemblyException::AssemblyException(ErrorLevel level, ErrorScope scope)
	: mLevel(level), mScope(scope) {}

AssemblyException::ErrorLevel AssemblyException::level() const {
	return mLevel;
}

AssemblyException::ErrorScope AssemblyException::scope() const {
	return mScope;
}

const char* AssemblyException::what() const noexcept {
	return mWhat.toStdString().c_str();
}

} // namespace tea
