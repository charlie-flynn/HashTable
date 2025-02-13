#include "HashTable.h"
#include <string>
#include <iostream>

// Creates an empty hash table of the given size.
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

// Creates a hash table of twice the size of the given initializer list, with the given contents inside.
HashTable::HashTable(std::initializer_list<const char*> values)
{
    m_count = 0;
    m_arrayLength = values.size() * 2;
    m_values = new HashPair[m_arrayLength];

    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }

    for (const char* value : values)
    {
        Add(value);
    }
}

// Creates a hash table of twice the size of the given character pointer array, with the given contents inside.
HashTable::HashTable(char* values[], int length)
{
    m_count = 0;
    m_arrayLength = length * 2;
    m_values = new HashPair[m_arrayLength];

    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }

    for (int i = 0; i < length; i++)
    {
        Add(values[i]);
    }
}

HashTable::~HashTable()
{
    delete[] m_values;
    m_values = nullptr;
}

// Returns a reference to the given value, or nullptr if it isn't in the table.
unsigned char*& HashTable::operator[](const char* key)
{
    unsigned int hashed = Hash((unsigned char*)key);
    unsigned int keyHashed = hashed % m_arrayLength;
    unsigned int index = keyHashed;
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength - 1 || m_values[index].hashed == 0)
        {
            unsigned char* nullpointer = nullptr;
            return nullpointer;
        }

        if (m_values[index].key == keyHashed)
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

// Adds the given value to the hash table, and returns whether it was successful or not.
bool HashTable::Add(const char* value)
{
    if (value == nullptr)
        return false;

    unsigned int hashed = Hash((unsigned char*)value);
    unsigned int key = hashed % m_arrayLength;
    unsigned int index = key;
    int numberSearched = 0;

    if (m_count >= m_arrayLength)
        return false;

    while (true)
    {
        if (numberSearched == m_arrayLength - 1 || m_values[index].hashed == hashed)
            return false;

        if (m_values[index].hashed == 0)
        {
            m_values[index] = HashPair(key, (unsigned char*)value, hashed);
            m_count++;
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

// Removes the given value to the hash table, and returns whether it was successful or not.
bool HashTable::Remove(const char* value)
{
    if (value == nullptr)
        return false;

    unsigned int hashed = Hash((unsigned char*)value);
    unsigned int key = hashed % m_arrayLength;
    unsigned int index = key;
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength - 1)
            return false;

        if (m_values[index].hashed != 0)
        {
            if (m_values[index].key == key)
            {
                if (m_values[index].hashed == hashed)
                {
                    m_values[index] = HashPair();
                    m_count--;
                    return true;
                }
            }
        }

        index = (index + 1) % m_arrayLength;
        numberSearched++;

    }

    return false;
}

// Resizes the hash table to the given size.
// NOTE: If the size is smaller than the current count, you will lose data!
void HashTable::Resize(int size)
{
    int copiedCount = 0;

    HashPair* newValues = new HashPair[size];
    int oldLength = m_arrayLength;
    m_arrayLength = size;
    for (int i = 0; i < oldLength; i++)
    {
        if (m_values[i].hashed != 0)
        {
            newValues[m_values[i].hashed % size] = HashPair(Hash(m_values[i].value) % size, m_values[i].value, m_values[i].hashed);   
            copiedCount++;
            if (copiedCount >= oldLength)
            {
                m_count = copiedCount;
                break;
            }
        }
    }
    delete[] m_values;
    m_values = newValues;
}

// Checks if the given value is contained in the hash table.
bool HashTable::Contains(char* value)
{
    return this->operator[](value) != nullptr;
}

// Hashes the given character pointer using ELF hash.
unsigned int HashTable::Hash(unsigned char* value)
{
    int length = ((std::string)(char*)value).length();
    unsigned int hash = 0, x = 0;
    for (int i = 0; i < length; i++)
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

// Clears the entire array, and reinitalizes it.
void HashTable::Clear()
{
    delete[] m_values;
    m_values = new HashPair[m_arrayLength];

    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }

    m_count = 0;
}
