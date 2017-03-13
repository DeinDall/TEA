#ifndef TEA_PRINTHINT_H
#define TEA_PRINTHINT_H

#include <QString>

namespace tea {

class PrintHint {
public:
	enum HintType {
		Continue,
		IgnoreScope,
		OpenScope,
		CloseScope,
		ResetScope
	};

public:
	PrintHint();
	PrintHint(HintType beforeHintType, HintType afterHintType);

	HintType beforeHint() const;
	HintType afterHint() const;

private:
	HintType mBeforeHint, mAfterHint;
};

} // namespace tea

#endif // TEA_PRINTHINT_H
