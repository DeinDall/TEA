#include "code.h"

#include "lang/core/code/codetemplate.h"
#include "core/rom/romutil.h"

#include "lang/disassembler/codedisassembler.h"

#include <QStringBuilder>

namespace tea {

Code::ConstParameterIterator::ConstParameterIterator(const Code* code)
	: mCode(code), mParameterIndex(-1), mComponentIndex(-1) {}

QString Code::ConstParameterIterator::name() const {
	return mCode->codeTemplate()->components().at(mComponentIndex).name();
}

quint64 Code::ConstParameterIterator::value() const {
	return mCode->parameterValue(mParameterIndex);
}

const CodeParameterType& Code::ConstParameterIterator::type() const {
	return mCode->codeTemplate()->components().at(mComponentIndex).type();
}

uint Code::ConstParameterIterator::offset() const {
	return mCode->codeTemplate()->components().at(mComponentIndex).offset();
}

bool Code::ConstParameterIterator::next() {
	QList<CodeTemplateComponent> components = mCode->codeTemplate()->components();

	do {
		if ((++mComponentIndex) >= components.size())
			return false;
	} while (components.at(mComponentIndex).isFixed());

	++mParameterIndex;
	return true;
}

Code::Code()
	: mTemplate(nullptr) {}

Code::Code(const CodeTemplate* templte, QVector<quint64> parameters)
	: mTemplate(templte), mParameters(parameters) {}

uint Code::size() const {
	return mTemplate->size();
}

const CodeTemplate* Code::codeTemplate() const {
	return mTemplate;
}

quint64 Code::parameterValue(uint index) const {
	return mParameters.at(index);
}

Code::ConstParameterIterator Code::parameterIterator() const {
	return ConstParameterIterator(this);
}

} // namespace tea
