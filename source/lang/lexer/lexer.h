#ifndef TEA_LEXER_H
#define TEA_LEXER_H

#include <QString>
#include <QObject>

#include "lang/core/assemblyline.h"
#include "lang/core/token.h"
#include "lang/error/assemblyexception.h"

#include "lexelet/abstractlexelet.h"

#include <QVector>
#include <QPair>

namespace tea {

class Lexer : public QObject {
	Q_OBJECT

public:
	using charCheckFunc_t = bool(*)(QChar);

public:
	Lexer(QObject* parent = nullptr);

protected:
	QStringRef tokenize(QStringRef ref);

signals:
	void tokenReady(tea::Token token);
	void error(tea::AssemblyException exception);
	void finished();

public slots:
	void handleLine(tea::AssemblyLine line);
	void finishLexing();

private:
	bool mErrored;

	QVector<QPair<charCheckFunc_t, AbstractLexelet*>> mLexelets;

	AssemblyLine mCurrentLine;
};

} // namespace tea

#endif // TEA_LEXER_H
