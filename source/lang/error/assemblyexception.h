#ifndef TEA_ASSEMBLYEXCEPTION_H
#define TEA_ASSEMBLYEXCEPTION_H

#include <exception>

#include <QVariant>

namespace tea {

class AssemblyException : public std::exception {
public:
	enum ErrorLevel {
		Error,
		Warning,
		Info,
		Debug
	};

	enum ErrorScope {
		Preprocessing,
		Parsing,
		Lexing,
		Assembling
	};

public:
	AssemblyException();
	AssemblyException(ErrorLevel level, ErrorScope scope, QString what);
	AssemblyException(ErrorLevel level, ErrorScope scope);

	ErrorLevel level() const;
	ErrorScope scope() const;

	const char* what() const noexcept;

private:
	ErrorLevel mLevel;
	ErrorScope mScope;
	QString mWhat;
};

} // namespace tea

#endif // TEA_ASSEMBLYEXCEPTION_H
