#include "codetemplate.h"

#include "rom/romutil.h"

namespace tea {

CodeTemplate::CodeTemplate()
	: mSize(0), mPriority(INT_MIN) {}

CodeTemplate::CodeTemplate(QString name)
	: mName(name), mSize(0), mPriority(0) {}

bool CodeTemplate::isValid() const {
	if (mName.isEmpty())
		return false;

	if (mSize == 0)
		return false;

	if (mTypes.isEmpty())
		return false;

	if (mNexts.isEmpty())
		return false;

	return true;
}

void CodeTemplate::setTypes(QStringList types) {
	mTypes = types;
}

void CodeTemplate::setNextTypes(QStringList nexts) {
	mNexts = nexts;
}

void CodeTemplate::setSize(int size) {
	mSize = size;
}

void CodeTemplate::setPriority(int priority) {
	mPriority = priority;
}

void CodeTemplate::setComponents(QList<CodeTemplateComponent> components) {
	mComponents = components;
}

void CodeTemplate::setPrintHint(PrintHint hint) {
	mPrintHint = hint;
}

QString CodeTemplate::name() const {
	return mName;
}

QStringList CodeTemplate::types() const {
	return mTypes;
}

QStringList CodeTemplate::nextTypes() const {
	return mNexts;
}

int CodeTemplate::size() const {
	return mSize;
}

int CodeTemplate::priority() const {
	return mPriority;
}

const QList<CodeTemplateComponent>& CodeTemplate::components() const {
	return mComponents;
}

PrintHint CodeTemplate::printHint() const {
	return mPrintHint;
}

uint CodeTemplate::argumentCount() const {
	uint count = 0;

	for (CodeTemplateComponent component : mComponents)
		if (!component.isFixed())
			++count;

	return count;
}

bool CodeTemplate::checkAgainst(ROMRef ref) const {
	for (CodeTemplateComponent component : mComponents) {
		if (component.isFixed()) {
			quint64 value = readNumber(ref.begin() + component.offset(),
									   qMin(ref.end(), ref.begin() + component.offset() + component.size()));
			if (component.fixedValue() != value)
				return false;
		}
	}

	return true;
}

Code CodeTemplate::makeCodeFrom(ROMRef ref) const {
	QVector<quint64> values;

	for (CodeTemplateComponent component : mComponents) {
		if (component.isFixed())
			continue;

		uint val = readNumber(ref.begin() + component.offset(),
							  qMin(ref.end(), ref.begin() + component.offset() + component.size()));

		values.append(val);
	}

	return Code(this, values);
}

} // namespace tea
