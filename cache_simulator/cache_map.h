#pragma once
#include <map>
#include <iostream>
class cache
{
public:
	struct line
	{
		int tag = 0;
		int counter = 0;
	};
	//init cache-> takes in size of cache and an optional associativity number
	void print_cache();
	void init_cache(int,int);
private:
	//map->index(set number),line
	std::map<int, line*> cache;
};

void cache::init_cache(int size, int associativity)
{
	for (int i = 0; i < size/32; i++)
	{
		line* l = new line;
		l->counter = 0x00000000;
		cache.emplace(i,l);
	}
}
void cache::print_cache()
{
	for (int i = 0; i < cache.size(); i++)
	{
		std::cout << i << " " << cache.at(i)->tag << std::endl;
	}
}