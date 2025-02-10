#pragma once
#include "HashPair.h"
#include <initializer_list>

class HashTable
{
private:
	HashPair* m_values;
	int m_length;
	int m_arrayLength;
public:
	HashTable(int size = 100);
	HashTable(char* values, int* valuesLength, int length);
	~HashTable();
	unsigned char* operator[](char* value, int length);
	bool Add(unsigned char* value, int length);
	bool Remove(unsigned char* value);
	int GetLength() { return m_length; }
	int GetArrayLength() { return m_arrayLength; }
	unsigned int Hash(unsigned char* value, int length);
};