#include <iostream>
#include "HashTable.h"

int main()
{
	HashTable hash = { "forty" };
	std::cout << hash[(char*)"forty"] << std::endl;
}
