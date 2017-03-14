#include "codetemplatecomponent.h"

namespace tea {

CodeTemplateComponent::CodeTemplateComponent(QString name)
	: mName(name), mOffset(0), mSize(0), mFixed(false), mFixedValue(0) {}

void CodeTemplateComponent::setTypes(QStringList types) {
	mTypeList = types;
}

void CodeTemplateComponent::setOffset(int offset) {
	mOffset = offset;
}

void CodeTemplateComponent::setSize(int size) {
	mSize = size;
}

void CodeTemplateComponent::setFixedValue(quint64 value) {
	mFixed = true;
	mFixedValue = value;
}

QString CodeTemplateComponent::name() const {
	return mName;
}

QStringList CodeTemplateComponent::types() const {
	return mTypeList;
}

int CodeTemplateComponent::offset() const {
	return mOffset;
}

int CodeTemplateComponent::size() const {
	return mSize;
}

bool CodeTemplateComponent::isFixed() const {
	return mFixed;
}

quint64 CodeTemplateComponent::fixedValue() const {
	return mFixedValue;
}

} // namespace tea
