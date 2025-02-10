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
	HashTable(std::initializer_list<const char*> values);
	HashTable(char* values, int length);
	~HashTable();
	unsigned char* operator[](char* value);
	bool Add(unsigned char* value);
	bool Remove(unsigned char* value);
	int GetLength() { return m_length; }
	int GetArrayLength() { return m_arrayLength; }
	unsigned int Hash(unsigned char* value);
};