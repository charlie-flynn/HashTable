#include <iostream>
#include "HashTable.h"

int main()
{
	HashTable hash = { "forty", "feeerty", "farty"};
	std::cout << hash[(char*)"forty"] << std::endl;
	std::cout << hash[(char*)"feeerty"] << std::endl;

	if (hash[(char*)("fraty")] != nullptr)
		std::cout << hash[(char*)"fraty"] << std::endl;


}
