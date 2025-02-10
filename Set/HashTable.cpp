#include "HashTable.h"
#include <string>
#include <iostream>

HashTable::HashTable(int size)
{
    m_length = size;
    m_arrayLength = m_length * 2;
    m_values = new HashPair();

    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }
}

HashTable::HashTable(std::initializer_list<const char*> values)
{
    m_length = values.size();
    m_arrayLength = m_length * 2;
    m_values = new HashPair();

    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }

    for (const char* value : values)
    {
        Add((unsigned char*)value);
    }
}

HashTable::HashTable(char* values, int length)
{
    m_length = length;
    m_arrayLength = m_length * 2;
    m_values = new HashPair();

    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }

    for (int i = 0; i < length; i++)
    {
        Add((unsigned char*)values[i]);
    }
}

HashTable::~HashTable()
{
    delete[] m_values;
}

unsigned char* HashTable::operator[](char* value)
{
    unsigned int key = Hash((unsigned char*)value);
    unsigned int index = key;
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength || &m_values[index] == nullptr)
            return nullptr;

        if (m_values[index].key == key)
            return m_values[index].value;
        else
        {
            index = (index + 1) % m_arrayLength;
            numberSearched++;
        }
    }
}

bool HashTable::Add(unsigned char* value)
{
    unsigned int hashed = Hash(value);
    unsigned int index = hashed % m_arrayLength;
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength)
            return false;

        if (m_values[index].key == HashPair().key)
        {
            if (m_values)
            m_values[index] = HashPair(index, value, ((std::string)(char*)value).length());
            return true;
        }
        else
        {
            index = (index + 1) % m_arrayLength;
            numberSearched++;
        }
    }

    return false;
}

bool HashTable::Remove(unsigned char* value)
{
    unsigned int index = Hash(value);
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength)
            return false;

        if (&m_values[index] != nullptr)
        {
            if (m_values[index].key == index)
            {
                m_values[index] = HashPair();
                return true;
            }
        }

        index = (index + 1) % m_arrayLength;
        numberSearched++;

    }

    return false;
}

unsigned int HashTable::Hash(unsigned char* value)
{
    int length = ((std::string)(char*)value).length();
    unsigned int hash = 0, x = 0;
    for (unsigned int i = 0; i < length; i++)
    {
        hash = (hash << 4) + value[i];
        if ((x = hash & 0xF0000000L) != 0) 
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
    return (hash & 0x7FFFFFFF);
}
