#include <iostream>
#include "Set.h"

int main()
{
    Set<int> set = Set<int>();

    set.Add(21);
    set.Add(22);
    set.Add(23);

    set.Remove(21);

    std::cout << set[22] << std::endl;
}
