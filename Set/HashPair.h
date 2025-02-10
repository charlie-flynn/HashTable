#pragma once

struct HashPair
{
public:
	unsigned int key;
	unsigned char* value;
	unsigned int valueLength;

	HashPair();
	HashPair(unsigned int key, unsigned char* value, int valueLength);
};



