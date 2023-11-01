#pragma once

#include <iostream>
#include <vector>

using std::string;
using std::endl;
using std::cout;

#define MESSAGE_TYPE_VAR unsigned short

template <typename V>
using Vector = std::vector<V>;

using Checksum = unsigned int;
using Unit32 = unsigned int;
using Unit16 = unsigned short;
using Package = Vector<char>;

class Packages
{
public:
	template<typename T>
	int countSetBits(T data);
	
	int countSetBits(const void* pData, int sizeofData);

	Checksum getChecksum(const void* pData, int sizeofData);

	Package getPackage(const void* pData, int sizeofData);

	bool isPackageValid(const Package& pack, Package* pOutPackage = nullptr);

	bool getPackageTypeAndData(const Package& pack, Unit16& msgType, Package& unpackdData);
};

