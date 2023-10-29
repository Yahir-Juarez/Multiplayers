#include "Packages.h"

template<typename T>
int countSetBits(T data) 
{
	int setBits = 0;
	for (int i = 0; i < sizeof(data) * 8; i++)
	{
		setBits += (data & (1 << i)) ? 1 : 0;
	}
	cout << setBits << endl;

	return setBits;
}

int countSetBits(const void* pData, int sizeofData)
{

}

Checksum getChecksum(const void* pData, int sizeofData)
{

}

Package getPackage(const void* pData, int sizeofData)
{

}

bool isPackageValid(const Package& pack)
{

}