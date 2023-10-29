#pragma once

#include <iostream>
#include <vector>

template <typename V>
using Vector = std::vector<V>;

using Checksum = unsigned int;
using Unit32 = unsigned int;
using Unit16 = unsigned short;
using Package = Vector<char>;

template<typename T>
class Packages
{
public:
	int countSetBits(T data);
	
	int countSetBits(const void* pData, int sizeofData);

	Checksum getChecksum(const void* pData, int sizeofData);

	Package getPackage(const void* pData, int sizeofData);

	bool isPackageValid(const Package& pack);

};

