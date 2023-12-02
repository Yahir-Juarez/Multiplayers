#include "Packages.h"

template<typename T>
int Packages::countSetBits(T data)
{
	int setBits = 0;
	for (int i = 0; i < sizeof(data) * 8; ++i)
	{
		setBits += (data & (1 << i)) ? 1 : 0;
	}

	return setBits;
}

int Packages::countSetBits(const void* pData, int sizeofData)
{
	int setBits = 0;

	const char* pDataInBytes = reinterpret_cast<const char*>(pData);

	for (int i = 0; i < sizeofData; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			setBits += (pDataInBytes[i] & (1 << j)) ? 1 : 0;
		}
	}

	return setBits;
}

Checksum Packages::getChecksum(const void* pData, int sizeofData)
{
	static Unit32 firm = 0xAAAA0000;
	int numBitsData = countSetBits(pData, sizeofData);
	int dataSize = countSetBits(sizeofData);

	return numBitsData + dataSize + firm;
}

Package Packages::getPackage(const void* pData, int sizeofData)
{
	Package newPackage;
	Checksum packageChecksum = getChecksum(pData, sizeofData);
	Unit16 dataSize = static_cast<Unit16>(sizeofData);

	newPackage.resize(sizeofData + sizeof(Unit16) + sizeof(packageChecksum));

	memcpy(&newPackage[0], &packageChecksum, sizeof(packageChecksum));
	memcpy(&newPackage[sizeof(packageChecksum)], &dataSize, sizeof(dataSize));
	memcpy(&newPackage[sizeof(packageChecksum) + sizeof(dataSize)], pData, dataSize);


	return newPackage;
}

bool Packages::isPackageValid(const Package& pack, Package* pOutPackage)
{
	if (pack.empty() || pack.size() < sizeof(Unit16) + sizeof(Checksum))
	{
		return false;
	}
	Checksum packCkecksum = 0;
	Unit16 dataSize = 0;

	Package packData;
	if (pOutPackage == nullptr)
	{
		pOutPackage = &packData;
	}

	memcpy(&packCkecksum, &pack[0], sizeof(packCkecksum));
	memcpy(&dataSize, &pack[sizeof(packCkecksum)], sizeof(dataSize));

	if (dataSize < 1) return false;

	pOutPackage->resize(dataSize);
	memcpy(pOutPackage->data(), &pack[sizeof(packCkecksum) + sizeof(dataSize)], dataSize);

	return (getChecksum(pOutPackage->data(), pOutPackage->size() == packCkecksum));
}

bool Packages::getPackageTypeAndData(const Package& pack, Unit16& msgType, Package& unpackdData)
{
	if (pack.size() < sizeof(MESSAGE_TYPE_VAR))
	{
		return false;
	}
	memcpy(&msgType, pack.data(), sizeof(MESSAGE_TYPE_VAR));

	if (!(pack.size() > sizeof(MESSAGE_TYPE_VAR)))
	{
		return true;
	}
	auto finalData = pack.size() - sizeof(MESSAGE_TYPE_VAR);
	unpackdData.resize(finalData);
	memcpy(unpackdData.data(), pack.data() + sizeof(MESSAGE_TYPE_VAR), finalData);
}