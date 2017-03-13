#ifndef TEA_ROM_H
#define TEA_ROM_H

#include <QString>
#include <QByteArray>

namespace tea {

class ROMRef;

class ROM {
public:
	using const_iterator = QByteArray::const_iterator;
public:
	ROM();

	void loadFromFile(QString fileName);

	char at(uint position) const;

	quint64 readNumber(uint byteCount) const;
	uint readPointer() const;

	uint size() const;

	inline const_iterator begin() const { return mData.cbegin(); }
	inline const_iterator end() const { return mData.cend(); }

	ROMRef ref() const;

	ROMRef midRef(uint pos) const;
	ROMRef midRef(uint pos, uint size) const;
	ROMRef leftRef(uint size) const;
	ROMRef rightRef(uint size) const;

private:
	QString mFileName;
	QByteArray mData;
};

} // namespace tea

#endif // TEA_ROM_H
