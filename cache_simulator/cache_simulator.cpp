
#include <iostream>
#include "cache_map.h"
//1.create 3 map-based caches
//  1.fully associative
//  2.direct mapped
//  3.n-associative cache
//2.

/*
* user will input size of cache
* each line will be a 32 bit address
* divide size of cache by number of bytes in line
* find offset: find out how to calculate offset
* *optional* find line number (only for non fully associative)
*/
int main()
{
    int selection = 0;
    int cache_type = 0;
    int size = 0;
    std::cout << "input the type of cache to be implemented:" << std::endl;
    std::cout << "type 1 for fully associative" << std::endl;
    std::cout << "type 2 for direct mapped" << std::endl;
    std::cout << "type 3 for n-associative" << std::endl;
    std::cin >> selection;
    if (selection == 1)
    {
        cache_type = 1;
    }
    else if (selection == 2)
    {
        cache_type = 2;
    }
    else if (selection == 3)
    {
        cache_type = 3;
    }

    std::cout << "how big (in bytes) will the cache be?" << std::endl;
    std::cin >> size;

    cache c;
    c.init_cache(size, 0);
    c.print_cache();


}
