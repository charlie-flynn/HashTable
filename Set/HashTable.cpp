#include "HashTable.h"

HashTable::HashTable(int size)
{
    m_length = size;
    m_arrayLength = m_length * 2;
    m_values = new Pair<unsigned int, unsigned char*>();
}

HashTable::HashTable(std::initializer_list<unsigned char*> values, int size)
{
    m_length = size;
    m_arrayLength = m_length * 2;
    m_values = new Pair<unsigned int, unsigned char*>();

    for (unsigned char* value : values)
    {
        Add(value);
    }
}

HashTable::HashTable(unsigned char* values, int length)
{
    m_length = length;
    m_arrayLength = m_length * 2;
    m_values = new Pair<unsigned int, unsigned char*>();

    for (int i = 0; i < length; i++)
    {
        Add(&values[i]);
    }
}

HashTable::~HashTable()
{
    delete[] m_values;
}

unsigned char* HashTable::operator[](unsigned char* value)
{
    unsigned int index = Hash(value);
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength)
            return nullptr;

        if (m_values[index].key == index)
            return m_values[index].value;
        else if (&m_values[index] == nullptr)
            return nullptr;
        else
        {
            index = (index + 1) % m_arrayLength;
            numberSearched++;
        }
    }
}

bool HashTable::Add(unsigned char* value)
{
    unsigned int index = Hash(value);
    int numberSearched = 0;

    while (true)
    {
        if (numberSearched == m_arrayLength)
            return false;

        if (&m_values[index] == nullptr)
        {
            m_values[index] = Pair<unsigned int, unsigned char*>(index, value);
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
                m_values[index] = Pair<unsigned int, unsigned char*>();
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
    unsigned int hash = 0, x = 0;
    for (unsigned int i = 0; i < m_arrayLength; ++i) 
    {
        hash = (hash << 4) + value[i];
        if ((x = hash & 0xF0000000L) != 0) 
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
    return (hash & 0x7FFFFFFF) % m_arrayLength;
}
