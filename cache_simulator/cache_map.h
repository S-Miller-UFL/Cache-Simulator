#pragma once
#include <map>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
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
	std::cout << "tag: " << tag <<std::endl;
	std::cout << "offset: " << offset << std::endl;
	std::cout << "line: " << line << std::endl;
	cache.at(std::stoll(line, nullptr, 2)) = (std::make_tuple(std::stoll(tag,nullptr,2), std::stoll(line,nullptr,2), std::stoll(offset,nullptr,2), 'F'));

}
void direct_cache::print()
{
	for (int i = 0; i < cache.size(); i++)
	{
		std::cout << std::get<0>(cache.at(i)) << std::endl;
	}
}

class set_cache
{
public:
	void populate(int, int,int, std::string);
	void initialize_cache(int);
	void print();
private:
	int hit = 0;
	int miss = 0;
	std::vector<std::tuple<int, int, int, char>> cache;

};
void set_cache::initialize_cache(int numberoflines)
{
	for (int i = 0; i < numberoflines; i++)
	{
		cache.push_back(std::make_tuple(0, 0, 0, 'E'));
	}
}
void set_cache::populate(int bytesinline, int numberoflines,int linesinset, std::string address)
{
	int offsetwidth = ceil(log2(bytesinline));
	int setwidth = ceil(log2(numberoflines/linesinset));
	int tagwidth = address.size() - offsetwidth - setwidth;
	std::string tag = address.substr(0, tagwidth);
	std::string offset = address.substr(tagwidth + setwidth, offsetwidth);
	std::string set = address.substr(tagwidth, setwidth);
	std::cout << "tag: " << tag << std::endl;
	std::cout << "offset: " << offset << std::endl;
	std::cout << "set: " << set << std::endl;
	int index = std::stoll(set, nullptr, 2) * linesinset; //first index of our set

		for (int i = 0; i < linesinset; i++)
		{
			if (std::get<0>(cache.at(index)) == std::stoll(tag, nullptr, 2) && std::get<3>(cache.at(index)) == 'F')
			{
				std::cout << "hit" << std::endl;
				hit++;
				break;
			}
			else if (std::get<3>(cache.at(index + i)) == 'E')
			{
				cache.at(index + i) = (std::make_tuple(std::stoll(tag, nullptr, 2), std::stoll(set, nullptr, 2), std::stoll(offset, nullptr, 2), 'F'));
				break;
			}
		}
		miss++;
		std::cout << "miss" << std::endl;
	
	/*
	* 0011 1111 1111 1111 1111 1000 00 000000
	* 0011 1111 1111 1111 1111 1000 00 000000
	* 0011 1111 1111 1111 1111 1000 01 000000
	* 0011 1111 1111 1111 1111 1000 01 000000
	* 0011 1111 1111 1111 1111 1000 10 000000
	* 0011 1111 1111 1111 1111 1000 10 000000
	* 0011 1111 1111 1111 1111 1000 11 000000
	* 0011 1111 1111 1111 1111 1000 11 000000
	*/

}
void set_cache::print()
{
	for (int i = 0; i < cache.size(); i++)
	{
		std::cout << "set: " << std::get<1>(cache.at(i))<< " tag: " << std::get<0>(cache.at(i)) << " offset: "<< std::get<2>(cache.at(i)) << std::endl;
	}
}
class fully_cache
{
public:
	void populate(int, int, std::string);
	void initialize_cache(int);
	void print();
private:
	int hit = 0;
	int miss = 0;
	std::vector<std::tuple<long long, long long, char>> cache;

};
void fully_cache::initialize_cache(int numberoflines)
{
	for (int i = 0; i < numberoflines; i++)
	{
		cache.push_back(std::make_tuple(0, 0, 'E'));
	}
}
void fully_cache::populate(int bytesinline, int numberoflines, std::string address)
{

	int offsetwidth = ceil(log2(bytesinline));
	int linewidth = 0;
	int tagwidth = address.size() - offsetwidth - linewidth;
	std::string tag = address.substr(0, tagwidth);
	std::string offset = address.substr(tagwidth + linewidth, offsetwidth);
	//std::string line = address.substr(tagwidth, linewidth);
	std::cout << "tag: " << tag << std::endl;
	std::cout << "offset: " << offset << std::endl;
	//std::cout << "line: " << line << std::endl;
	for (int i = 0; i < cache.size(); i++)
	{
		
		if ((std::get<2>(cache.at(i))) == 'F' && (std::get<0>(cache.at(i)) == std::stoll(tag, nullptr, 2)))
		{
			hit++;
			break;
		}
		else if (std::get<2>(cache.at(i)) == 'E')
		{
			cache.at(i) = (std::make_tuple(std::stoll(tag, nullptr, 2), std::stoll(offset, nullptr, 2), 'F'));
			miss++;
			break;
		}
	}
	

}
void fully_cache::print()
{
	for (int i = 0; i < cache.size(); i++)
	{
		std::cout << std::get<0>(cache.at(i)) << std::endl;
	}
}
long binarystringtolong(std::string str)
{
	for (int i = str.size(); i > 0; i--)
	{

	}
	return 0;
}