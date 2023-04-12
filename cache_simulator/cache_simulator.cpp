
#include <iostream>
#include "cache_map.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>
#include <bitset>
#include <algorithm>
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
int hextoint(std::string);
std::string hextobin(std::string);
int bintoint(std::string);
int main()
{
    int selection = 0;
    int cache_type = 0;
    int size = 0;
    int linesize = 0;
    int hit = 0;
    int miss = 0;
    std::cout << "input the type of cache to be implemented:" << std::endl;
    std::cout << "type 1 for direct mapped" << std::endl;
    std::cout << "type 2 for fully associative" << std::endl;
    std::cout << "type 3 for n-associative" << std::endl;
    std::cin >> selection;

    std::cout << "how big (in bytes) will the cache be?" << std::endl;
    std::cin >> size;
    std::cout << "how big will a block be?" << std::endl;
    std::cin >> linesize;
    char byte;
    short count;
    std::string line;
    std::string input;
    std::vector<std::string> v;
    std::ifstream file("gcc.trace");
    if (file.is_open())
    {
        while (std::getline(file,input))
        {
            std::stringstream stream(input);
            //file.read(&byte, 1);
            //file.read(&byte, 1);

            getline(stream,line, '\n');
            line = line.substr(line.find('x')+1,line.length()-line.find('x'));
            line = line.substr(0, line.find(' '));
            v.push_back(line);

        }
        file.close();
    }
    else
    {
        std::cout << "cannot find file" << std::endl;
    }
    for (int i = 0; i < v.size(); i++)
    {
        v.at(i) = hextobin(v.at(i));
        //std::cout << v.at(i) << std::endl;
    }
    int policy = 0;
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
        //512
        dc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            dc.populate(linesize, size / linesize, v.at(i));
        }
        //dc.populate(linesize, size / linesize, v.at(0));
        std::cout << "size: " << size << std::endl;
        dc.print();
        //1024
        size = size * 2;
        dc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            dc.populate(linesize, size / linesize, v.at(i));
        }
        //dc.populate(linesize, size / linesize, v.at(0));
        std::cout << "size: " << size << std::endl;
        dc.print();
        //2048
        size = size * 2;
        dc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            dc.populate(linesize, size / linesize, v.at(i));
        }
        //dc.populate(linesize, size / linesize, v.at(0));
        std::cout << "size: " << size << std::endl;
        dc.print();
        //4096
        size = size * 2;
        dc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            dc.populate(linesize, size / linesize, v.at(i));
        }
        //dc.populate(linesize, size / linesize, v.at(0));
        std::cout << "size: " << size << std::endl;
        dc.print();
        //8192
        size = size * 2;
        dc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            dc.populate(linesize, size / linesize, v.at(i));
        }
        //dc.populate(linesize, size / linesize, v.at(0));
        std::cout << "size: " << size << std::endl;
        dc.print();
        //16384
        size = size * 2;
        dc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            dc.populate(linesize, size / linesize, v.at(i));
        }
        //dc.populate(linesize, size / linesize, v.at(0));
        std::cout << "size: " << size << std::endl;
        dc.print();
    }
    else if (selection == 2)
    {
        std::cout << "FIFO or LRU for replacement policy?" << std::endl;
        std::cout << "0: LRU" << std::endl;
        std::cout << "1: FIFO" << std::endl;
        std::cin >> policy;
        /*
        * full associative
        */
        fully_cache fc;
        //1.convert to binary

        //2. split tag/offset
        //512
        fc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            fc.populate(linesize, size / linesize, v.at(i),policy);
        }
        std::cout << "size: " << size << std::endl;
        fc.print();
        //1024
        size = size * 2;
        fc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            fc.populate(linesize, size / linesize, v.at(i), policy);
        }
        std::cout << "size: " << size << std::endl;
        fc.print();
        //2048
        size = size * 2;
        fc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            fc.populate(linesize, size / linesize, v.at(i), policy);
        }
        std::cout << "size: " << size << std::endl;
        fc.print();
        //4096
        size = size * 2;
        fc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            fc.populate(linesize, size / linesize, v.at(i), policy);
        }
        std::cout << "size: " << size << std::endl;
        fc.print();
        //8196
        size = size * 2;
        fc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            fc.populate(linesize, size / linesize, v.at(i), policy);
        }
        std::cout << "size: " << size << std::endl;
        fc.print();
        //16384
        size = size * 2;
        fc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            fc.populate(linesize, size / linesize, v.at(i), policy);
        }
        std::cout << "size: " << size << std::endl;
        fc.print();
    }
    else if (selection == 3)
    {
        std::cout << "FIFO or LRU for replacement policy?" << std::endl;
        std::cout << "0: LRU" << std::endl;
        std::cout << "1: FIFO" << std::endl;
        std::cin >> policy;
        /*
        * set associative map
        */
        //1.convert to binary
        //2.split tag/set/offset
        int linesinset = 0;
        std::cout << "how many lines per set?" << std::endl;
        std::cin >> linesinset;
        set_cache sc;
        sc.initialize_cache(size / linesize, linesinset);
        for (int i = 0; i < v.size(); i++)
        {
            sc.populate(linesize, size / linesize, linesinset,v.at(i),policy);
        }
        sc.print();
    }
    else if (selection == 4)
    {
        int linesinset = 0;
        std::cout << "how many lines per set?" << std::endl;
        std::cin >> linesinset; 

        //direct cache
        direct_cache dc;
        dc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            dc.populate(linesize, size / linesize, v.at(i));
        }
        std::cout << "direct associative: " << std::endl;
        dc.print();

        /*
        * full associative lru
        */
        fully_cache fc;
        fc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            fc.populate(linesize, size / linesize, v.at(i), 0);
        }
        std::cout << "fully associative LRU: " << std::endl;
        fc.print();
        /*
        * full associative fifo
        */
        fc.initialize_cache(size / linesize);
        for (int i = 0; i < v.size(); i++)
        {
            fc.populate(linesize, size / linesize, v.at(i), 1);
        }
        std::cout << "fully associative FIFO: " << std::endl;
        fc.print();
        //set cache lru
        set_cache sc;
        sc.initialize_cache(size / linesize, linesinset);
        for (int i = 0; i < v.size(); i++)
        {
            sc.populate(linesize, size / linesize, linesinset, v.at(i), 0);
        }
        std::cout << "set associative LRU: " << std::endl;
        sc.print();
        //set cache fifo
        sc.initialize_cache(size / linesize, linesinset);
        for (int i = 0; i < v.size(); i++)
        {
            sc.populate(linesize, size / linesize, linesinset, v.at(i), 1);
        }
        std::cout << "set associative FIFO: " << std::endl;
        sc.print();
    }
    else if (selection == 5)
    {
    //because im fucking lazy
    std::cout << "FIFO or LRU for replacement policy?" << std::endl;
    std::cout << "0: LRU" << std::endl;
    std::cout << "1: FIFO" << std::endl;
    std::cin >> policy;
    /*
    * set associative map
    */
    //1.convert to binary
    //2.split tag/set/offset
    int linesinset = 0;
    std::cout << "how many lines per set?" << std::endl;
    std::cin >> linesinset;
    set_cache sc;
    //512
    sc.initialize_cache(size / linesize, linesinset);
    for (int i = 0; i < v.size(); i++)
    {
        sc.populate(linesize, size / linesize, linesinset, v.at(i), policy);
    }
    std::cout << "cache size: " << size << std::endl;
    sc.print();
    //1024
    size = size * 2;
    sc.initialize_cache((size) / linesize, linesinset);
    for (int i = 0; i < v.size(); i++)
    {
        sc.populate(linesize, size / linesize, linesinset, v.at(i), policy);
    }
    std::cout << "cache size: " << size << std::endl;
    sc.print();
    //2048
    size = size * 2;
    sc.initialize_cache((size) / linesize, linesinset);
    for (int i = 0; i < v.size(); i++)
    {
        sc.populate(linesize, size / linesize, linesinset, v.at(i), policy);
    }
    std::cout << "cache size: " << size << std::endl;
    sc.print();
    //4096
    size = size * 2;
    sc.initialize_cache((size) / linesize, linesinset);
    for (int i = 0; i < v.size(); i++)
    {
        sc.populate(linesize, size / linesize, linesinset, v.at(i), policy);
    }
    std::cout << "cache size: " << size << std::endl;
    sc.print();
    //8192
    size = size * 2;
    sc.initialize_cache((size) / linesize, linesinset);
    for (int i = 0; i < v.size(); i++)
    {
        sc.populate(linesize, size / linesize, linesinset, v.at(i), policy);
    }
    std::cout << "cache size: " << size << std::endl;
    sc.print();
    //16384
    size = size * 2;
    sc.initialize_cache((size) / linesize, linesinset);
    for (int i = 0; i < v.size(); i++)
    {
        sc.populate(linesize, size / linesize, linesinset, v.at(i), policy);
    }
    std::cout << "cache size: " << size << std::endl;
    sc.print();
    
    }
}

std::string hextobin(std::string hex)
{
    std::transform(hex.begin(), hex.end(), hex.begin(), ::toupper);
    int val = 0;
    std::string binary = "";
    for (int i = 0; i < hex.length(); i++)
    {
        if (hex.at(i) == 'A')
        {
            binary += "1010";
        }
        else if (hex.at(i) == 'B')
        {
            binary += "1011";
        }
        else if (hex.at(i) == 'C')
        {
            binary += "1100";
        }
        else if (hex.at(i) == 'D')
        {
            binary += "1101";
        }
        else if (hex.at(i) == 'E')
        {
            binary += "1110";
        }
        else if (hex.at(i) == 'F')
        {
            binary += "1111";
        }
        else if (hex.at(i) == '0')
        {
            binary += "0000";
        }
        else if (hex.at(i) == '1')
        {
            binary += "0001";
        }
        else if (hex.at(i) == '2')
        {
            binary += "0010";
        }
        else if (hex.at(i) == '3')
        {
            binary += "0011";
        }
        else if (hex.at(i) == '4')
        {
            binary += "0100";
        }
        else if (hex.at(i) == '5')
        {
            binary += "0101";
        }
        else if (hex.at(i) == '6')
        {
            binary += "0110";
        }
        else if (hex.at(i) == '7')
        {
            binary += "0111";
        }
        else if (hex.at(i) == '8')
        {
            binary += "1000";
        }
        else if (hex.at(i) == '9')
        {
            binary += "1001";
        }


    }
    return binary;
}
int hextoint(std::string hex)
{
    std::transform(hex.begin(), hex.end(), hex.begin(), ::toupper);
    int val = 0;
    std::string binary = "";
    for (int i = 0; i < hex.length(); i++)
    {
        if (hex.at(i) == 'A')
        {
            binary += "1010";
        }
        else if (hex.at(i) == 'B')
        {
            binary += "1011";
        }
        else if (hex.at(i) == 'C')
        {
            binary += "1100";
        }
        else if (hex.at(i) == 'D')
        {
            binary += "1101";
        }
        else if (hex.at(i) == 'E')
        {
            binary += "1110";
        }
        else if (hex.at(i) == 'F')
        {
            binary += "1111";
        }
        else if (hex.at(i) == '0')
        {
            binary += "0000";
        }
        else if (hex.at(i) == '1')
        {
            binary += "0001";
        }
        else if (hex.at(i) == '2')
        {
            binary += "0010";
        }
        else if (hex.at(i) == '3')
        {
            binary += "0011";
        }
        else if (hex.at(i) == '4')
        {
            binary += "0100";
        }
        else if (hex.at(i) == '5')
        {
            binary += "0101";
        }
        else if (hex.at(i) == '6')
        {
            binary += "0110";
        }
        else if (hex.at(i) == '7')
        {
            binary += "0111";
        }
        else if (hex.at(i) == '8')
        {
            binary += "1000";
        }
        else if (hex.at(i) == '9')
        {
            binary += "1001";
        }


    }
    for (int i = 0; i < binary.length(); i++)
    {
        val += (binary.at(i) - 48)*pow(2,(binary.length()-1)-i);
    }
    //std::cout << binary << std::endl;
    //std::cout << val << std::endl;
    return val;
}

//your hit rates seem off, try using a map.
/*
* 512 byte cache:
* direct mapped: 0.785403
* LRU:
* fully associative:0.927607
* set associative: 0.828462
* FIFO:
* fully associative: 0.911052
* set associative: 0.819589
* 
* 1024 byte cache:
* direct mapped: 0.831627
* LRU:
* fully associative:0.980232
* set associative: 0.891239
* FIFO:
* fully associative: 0.973668
* set associative: 0.884747
* direct mapped should be lowest
* set should be inbetween
* fully associative should be highest
*/