#include "HashPair.h"

HashPair::HashPair() : key(0), value(nullptr), valueLength(0)
{
}

HashPair::HashPair(unsigned int key, unsigned char* value, int valueLength) : key(key), value((unsigned char*)value), valueLength(valueLength)
{
}
