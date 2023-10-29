#include "Packages.h"

template<typename T>
int countSetBits(T data) 
{
	int setBits = 0;
	for (int i = 0; i < sizeof(data) * 8; i++)
	{
		setBits += (data & (1 << i)) ? 1 : 0;
	}

	return setBits;
}

int countSetBits(const void* pData, int sizeofData)
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

Checksum getChecksum(const void* pData, int sizeofData)
{
	static Unit32 firm = 0xFFFF0000;
	int numBitsData = countSetBits(pData, sizeofData);
	int dataSize = countSetBits(sizeofData);

	return numBitsData + dataSize + firm;
}

Package getPackage(const void* pData, int sizeofData)
{
	Package newPackage;
	Checksum packageChecksum = getChecksum(pData, sizeofData);
	Unit16 dataSize = sizeofData;

	newPackage.resize(sizeofData + sizeof(short) + sizeof(packageChecksum));

	memcpy(&newPackage[0], &packageChecksum, sizeof(packageChecksum));
	memcpy(&newPackage[sizeof(packageChecksum)], &dataSize, sizeof(dataSize));
	memcpy(&newPackage[sizeof(packageChecksum) + sizeof(dataSize)], pData, dataSize);


	return newPackage;
}

bool isPackageValid(const Package& pack)
{
	if (pack.empty() || pack.size() < sizeof(Unit16) + sizeof(Checksum))
	{
		return false;
	}
	Checksum packCkecksum = 0;
	Unit16 dataSize = 0;
	Vector<char> packData;

	memcpy(&packCkecksum, &pack[0], sizeof(packCkecksum));
	memcpy(&dataSize, &pack[sizeof(packCkecksum)], sizeof(dataSize));

	if (dataSize < 1) return false;

	packData.resize(dataSize);
	memcpy(&packData[0], &pack[sizeof(packCkecksum) + sizeof(dataSize)], dataSize);

	return (getChecksum(packData.data(), packData.size() == packCkecksum));
}