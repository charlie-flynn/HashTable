#pragma once
#include "Pair.h"
#include <initializer_list>

class HashTable
{
private:
	Pair<unsigned int, unsigned char*>* m_values;
	int m_length;
	int m_arrayLength;
public:
	HashTable(int size = 100);
	HashTable(std::initializer_list<unsigned char*> values, int size);
	HashTable(unsigned char* values, int length);
	~HashTable();
	unsigned char* operator[](unsigned char* value);
	bool Add(unsigned char* value);
	bool Remove(unsigned char* value);
	int GetLength() { return m_length; }
	int GetArrayLength() { return m_arrayLength; }
	unsigned int Hash(unsigned char* value);
};