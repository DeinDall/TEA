#include "printhint.h"

namespace tea {

PrintHint::PrintHint()
	: PrintHint(Continue, Continue) {}

PrintHint::PrintHint(HintType beforeHintType, HintType afterHintType)
	: mBeforeHint(beforeHintType), mAfterHint(afterHintType) {}

PrintHint::HintType PrintHint::beforeHint() const {
	return mBeforeHint;
}

PrintHint::HintType PrintHint::afterHint() const {
	return mAfterHint;
}

} // namespace tea
