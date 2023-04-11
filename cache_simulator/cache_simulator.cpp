
#include <iostream>
#include "cache_map.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>
#include <bitset>
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
    int linesize = 0;
    int hit = 0;
    int miss = 0;
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
    std::cout << "how big will a block be?" << std::endl;
    std::cin >> linesize;
    char byte;
    short count;
    std::string line;
    std::vector<std::string> v;
    std::ifstream file("read01.trace",std::ios_base::binary);
    if (file.is_open())
    {
        while (!file.eof())
        {
            file.read(&byte, 1);
            file.read(&byte, 1);
            //file.read(&byte, 1);
            //file.read(&byte, 1);
            for (int i = 0; i < 11; i++)
            {
                file.read(&byte, 1);
                if (byte != '\n')
                {
                    line = line + byte;
                }
                //line = line + byte;
                
            }
            file.read(&byte, 1);
            file.read(&byte, 1);
            if (line.size() != 0)
            {
                v.push_back(line);
            }
            line = "";

        }
        file.close();
    }
    else
    {
        std::cout << "cannot find file" << std::endl;
    }
    for (int i = 0; i < v.size(); i++)
    {
        int val = std::stol(v.at(i), nullptr, 16);
        v.at(i) = std::bitset<32>(val).to_string();
        //std::cout << v.at(i) << std::endl;
    }
    if (selection == 1)
    {


        //directed map
        /*
        * split into appropriate fields
        - if Direct Mapped then: Tag/Line/Offset
        - if Set Associative then: Tag/Set/Offset
        - if Fully Associative then: Tag/Offset
        */

        /*
        * 1.convert to binary
        */
        //2.split tag line offset

        //3.store in data structure
        direct_cache dc;
        dc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            dc.populate(linesize, size / linesize, v.at(i));
        }
        //dc.populate(linesize, size / linesize, v.at(0));
        dc.print();
    }
    else if (selection == 2)
    {
        /*
        * full associative
        */
        fully_cache fc;
        //1.convert to binary

        //2. split tag/offset
        fc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            fc.populate(linesize, size / linesize, v.at(i));
        }
        fc.print();
    }
    else if (selection == 3)
    {
        /*
        * set associative map
        */
        //1.convert to binary
        //2.split tag/set/offset
        int linesinset = 0;
        std::cout << "how many sets per line?" << std::endl;
        std::cin >> linesinset;
        set_cache sc;
        sc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            if (sc.populate(linesize, size / linesize, linesinset, v.at(i))==true)
            {
                hit++;
            }
            else
            {
                miss++;
            }
        }
        sc.print();
    }
    std::cout << "hit: " << hit << std::endl;
    std::cout << "miss: " << miss << std::endl;
}
