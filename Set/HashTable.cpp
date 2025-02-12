#include "HashTable.h"
#include <string>
#include <iostream>

HashTable::HashTable(int size)
{
    m_count = 0;
    m_arrayLength = size;
    m_values = new HashPair[m_arrayLength];

    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }
}

HashTable::HashTable(std::initializer_list<const char*> values)
{
    m_count = values.size();
    m_arrayLength = m_count * 2;
    m_values = new HashPair[m_arrayLength];

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
    m_count = length;
    m_arrayLength = m_count * 2;
    m_values = new HashPair[m_arrayLength];

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
    m_values = nullptr;
}

unsigned char*& HashTable::operator[](char* value)
{
    unsigned int hashed = Hash((unsigned char*)value);
    unsigned int key = hashed % m_arrayLength;
    unsigned int index = key;
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength - 1 || m_values[index].hashed == 0)
        {
            unsigned char* placeholder = nullptr;
            return placeholder;
        }

        if (m_values[index].key == key)
        {
            if (m_values[index].hashed == hashed)
            {
                return m_values[index].value;
            }
        }

        index = (index + 1) % m_arrayLength;
        numberSearched++;
    }
}

bool HashTable::Add(unsigned char* value)
{
    unsigned int hashed = Hash(value);
    unsigned int key = hashed % m_arrayLength;
    unsigned int index = key;
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength - 1 || m_values[index].hashed == hashed)
            return false;

        if (m_values[index].key == HashPair().key)
        {
            m_values[index] = HashPair(key, value, hashed);
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
    unsigned int hashed = Hash(value);
    unsigned int index = hashed % m_arrayLength;
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength - 1)
            return false;

        if (m_values[index].hashed != 0)
        {
            if (m_values[index].key == index)
            {
                if (m_values[index].hashed == hashed)
                {
                    m_values[index] = HashPair();
                    m_count++;
                    return true;
                }
            }
        }

        index = (index + 1) % m_arrayLength;
        numberSearched++;

    }

    return false;
}

void HashTable::Resize(int size)
{
    HashPair* newValues = new HashPair[size];
    int oldLength = m_arrayLength;
    m_arrayLength = size;
    for (int i = 0; i < oldLength; i++)
    {
        if (m_values[i].hashed != 0)
            newValues[m_values[i].hashed % size] = HashPair(Hash(m_values[i].value) % size, m_values[i].value, m_values[i].hashed);   
    }
    delete[] m_values;
    m_values = newValues;
}

bool HashTable::Contains(char* value)
{
    return this->operator[](value) != nullptr;
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
