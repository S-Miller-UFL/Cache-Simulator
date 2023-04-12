#pragma once
#include <map>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <queue>
int counter = 1;
int slots = 0;
int bintoint(std::string binary)
{
	int val = 0;
	for (int i = 0; i < binary.length(); i++)
	{
		val += (binary.at(i) - 48) * pow(2, (binary.length() - 1) - i);
	}
	//std::cout << binary << std::endl;
	//std::cout << val << std::endl;
	return val;
}
class direct_cache
{
public:
	void populate(int, int,std::string);
	void initialize_cache(int);
	void print();
private:
	int hit = 0;
	int miss = 0;
	//std::map<int,block*> cache;
	std::vector <std::tuple<long long, long long , long long, char >> cache;
	float hitrate = 0;
};
void direct_cache::initialize_cache(int numberoflines)
{
	for (int i = 0; i < numberoflines; i++)
	{
		cache.push_back(std::make_tuple(0, 0, 0, 'E'));
	}
}
void direct_cache::populate(int bytesinline,int numberoflines,std::string address)
{
	int offsetwidth = ceil(log2(bytesinline));
	int linewidth = log2(numberoflines);
	int tagwidth = address.size() - offsetwidth - linewidth;
	std::string tag = address.substr(0,tagwidth);
	std::string offset = address.substr(tagwidth+linewidth,offsetwidth);
	std::string line = address.substr(tagwidth, linewidth);
	

		if ((std::get<0>(cache.at(bintoint(line))) == bintoint(tag)) && (std::get<3>(cache.at(bintoint(line) == 'F'))))
		{
			//std::cout << "tag: " << stoll(tag, nullptr, 2) << std::endl;
			//std::cout << "offset: " << offset << std::endl;
			//std::cout << "line: " << line << std::endl;
			//std::cout << "hit" << std::endl;
			hit++;
		}
		else
		{
		cache.at(bintoint(line)) = (std::make_tuple(bintoint(tag), bintoint(line), bintoint(offset), 'F'));
		//std::cout << "tag: " << bintoint(tag) << std::endl;
		//std::cout << "offset: " << offset << std::endl;
		//std::cout << "line: " << line << std::endl;
		//std::cout << "miss" << std::endl;
		miss++;
		}


}
void direct_cache::print()
{
	for (int i = 0; i < cache.size(); i++)
	{
		std::cout << std::get<0>(cache.at(i)) << std::endl;
	}
	hitrate = (float)hit / (float)(hit + miss);

	std::cout << "hit: " << hit << std::endl;
	std::cout << "miss: " << miss << std::endl;
	std::cout << "hit rate: " << hitrate << std::endl;
}

class set_cache
{
public:
	void populate(int, int, int, std::string, int);
	void initialize_cache(int,int);
	void print();
private:
	int hit = 0;
	int miss = 0;
	float hitrate = 0;
	std::vector<std::tuple<int, int, int, char, int>> cache;
	int biggest = 0;

};
void set_cache::initialize_cache(int numberoflines, int linesperset)
{
	if (cache.size() > 0)
	{
		cache.clear();
	}
	for (int i = 0; i < numberoflines; i++)
	{
		cache.push_back(std::make_tuple(0, 0, 0, 'E', 0));
	}
	counter = 1;
	slots = 0;
	hit = 0;
	miss = 0;
}
void set_cache::populate(int bytesinline, int numberoflines, int linesinset, std::string address, int policy)
{
	int offsetwidth = ceil(log2(bytesinline));
	int setwidth = ceil(log2(numberoflines / linesinset));
	int tagwidth = address.size() - offsetwidth - setwidth;
	std::string tag = address.substr(0, tagwidth);
	std::string offset = address.substr(tagwidth + setwidth, offsetwidth);
	std::string set = address.substr(tagwidth, setwidth);
	int setnum = bintoint(set);
	int index = setnum * linesinset; //first index of our set
	bool hitted = false;
	int lowest = counter;
	int slots = 0;
	counter++;

		for (int i = 0; i < linesinset; i++)
		{
			//we hit a value
			if (std::get<0>(cache.at(index)) == bintoint(tag) && std::get<3>(cache.at(index)) == 'F')
			{
				//std::cout << "tag: " << stoll(tag, nullptr, 2) << std::endl;
				//std::cout << "offset: " << offset << std::endl;
				//std::cout << "set: " << set << std::endl;
				hit++;
				hitted = true;
				if (policy == 0)
				{
					counter++;
					//reset counter value to zero
					cache.at(index) = (std::make_tuple(bintoint(tag), bintoint(set), bintoint(offset), 'F', counter));
				}
				break;
			}
		}
		//if hit is equal to false
		//iterate through our set
		// find out which ones are full
		//if set is full ,iterate again and find which value has the lesser counter value
		//iterate again, increment counter, and perform a replacement
		if (hitted == false)
		{
			miss++;
			for (int i = 0; i < linesinset; i++)
			{
				//find if were full
				if (std::get<3>(cache.at(index + i)) == 'F')
				{
					slots++;
				}
				else if(std::get<3>(cache.at(index + i)) == 'E')
				{
				   cache.at(index+i) = (std::make_tuple(bintoint(tag), bintoint(set), bintoint(offset), 'F', counter));
				   break;
				}
			}
			//if were full
			if (slots == linesinset)
			{
				for (int i = 0; i < linesinset; i++)
				{
					//find lowest
					if (std::get<4>(cache.at(index + i)) < counter)
					{
						lowest = std::get<4>(cache.at(index));
					}
				}
				for (int i = 0; i < linesinset; i++)
				{
					//replace
					if (std::get<4>(cache.at(index + i)) = lowest)
					{
						cache.at(index) = (std::make_tuple(bintoint(tag), bintoint(set), bintoint(offset), 'F', counter));
					}
					break;
				}
			}
			
		}
	
}
void set_cache::print()
{
	for (int i = 0; i < cache.size(); i++)
	{
		std::cout << "set: " << std::get<1>(cache.at(i))<< " tag: " << std::get<0>(cache.at(i)) << " offset: "<< std::get<2>(cache.at(i)) << std::endl;
	}
	hitrate = (float)hit / (float)(hit + miss);
	std::cout << "hit: " << hit << std::endl;
	std::cout << "miss: " << miss << std::endl;
	std::cout << "hit rate: " << hitrate << std::endl;
}
class fully_cache
{
public:
	void populate(int, int, std::string,int);
	void initialize_cache(int);
	void print();
private:
	int hit = 0;
	int miss = 0;
	float hitrate = 0;
	int biggest = 0;
	int taken = 0;
	std::vector<std::tuple<long long, long long, char, int>> cache;
};
void fully_cache::initialize_cache(int numberoflines)
{
	if (cache.size() > 0)
	{
		cache.clear();
	}
	for (int i = 0; i < numberoflines; i++)
	{
		cache.push_back(std::make_tuple(0, 0, 'E',0));
	}
	counter = 1;
	slots = 0;
	hit = 0;
	miss = 0;
}
void fully_cache::populate(int bytesinline, int numberoflines, std::string address, int policy)
{

	int offsetwidth = ceil(log2(bytesinline));
	int linewidth = 0;
	int tagwidth = address.size() - offsetwidth - linewidth;
	std::string tag = address.substr(0, tagwidth);
	std::string offset = address.substr(tagwidth + linewidth, offsetwidth);
	bool hitted = false;
	int lowest = counter;
	counter++;

	//check if its a hit or a miss
	//if its a hit, and the policy is equal to 0, then we increment the counter and replace the datas counter with our new one
	//if its a miss, we need to add the data
	//first, we increment the counter.
	//then, we check which line has the lowest counter. we replace that line with our new line. and with our new counter value.
	for (int i = 0; i < numberoflines; i++)
	{
		if (std::get<0>(cache.at(i)) == bintoint(tag) && std::get<3>(cache.at(i)) == 'F')
		{
			if (policy == 0)
			{
				counter++;
				cache.at(i) = (std::make_tuple(bintoint(tag), bintoint(offset), 'F', counter));
			}
			hit++;
			hitted = true;
			break;
		}
	}
	//our data doesnt exist,we need to add it.
	if (hitted == false)
	{
		miss++;
		//our cache is full
		if (slots == numberoflines) 
		{
			for (int i = 0; i < numberoflines; i++)
			{
				if (std::get<3>(cache.at(i)) < lowest)
				{
					lowest = std::get<3>(cache.at(i));
					
				}
			}
			//find the lowest counter data
			for (int i = 0; i < numberoflines; i++)
			{
				if (std::get<3>(cache.at(i)) == lowest)
				{
					cache.at(i) = (std::make_tuple(bintoint(tag), bintoint(offset), 'F', counter));
					break;
				}
			}

		}
		else
		{
			//find an empty slot
			for (int i = 0; i < numberoflines; i++)
			{
				if (std::get<2>(cache.at(i)) == 'E')
				{
					cache.at(i) = (std::make_tuple(bintoint(tag), bintoint(offset), 'F', counter));
					slots++;

				}
			}
		}
	
	}
	
	

}
void fully_cache::print()
{
	for (int i = 0; i < cache.size(); i++)
	{
		std::cout << std::get<0>(cache.at(i)) << std::endl;
	}
	hitrate = (float)hit / (float)(hit + miss);
	std::cout << "hit: " << hit << std::endl;
	std::cout << "miss: " << miss << std::endl;
	std::cout << "hit rate: " << hitrate << std::endl;
}

