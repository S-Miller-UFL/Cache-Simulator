#pragma once
#include <map>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <queue>
int counter = 0;
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
	//use map instead
	//std::map<line,tag>
	std::map <int, int> cache;
	float hitrate = 0;
};
void direct_cache::initialize_cache(int numberoflines)
{
	if (cache.size() > 0)
	{
		cache.clear();
	}
	for (int i = 0; i < numberoflines; i++)
	{
		cache.emplace(i, 0);
	}
	counter = 0;
	slots = 0;
	hit = 0;
	miss = 0;

}
void direct_cache::populate(int bytesinline,int numberoflines,std::string address)
{
	int offsetwidth = ceil(log2(bytesinline));
	int linewidth = log2(numberoflines);
	int tagwidth = address.size() - offsetwidth - linewidth;
	std::string tag = address.substr(0,tagwidth);
	std::string offset = address.substr(tagwidth+linewidth,offsetwidth);
	std::string line = address.substr(tagwidth, linewidth);
	int linenumber = bintoint(line);
	int tagnumber = bintoint(tag);
	auto it = cache.find(linenumber);
	//we have a potential hit
			//std::cout << "tag: " << stoll(tag, nullptr, 2) << std::endl;
			//std::cout << "offset: " << offset << std::endl;
			//std::cout << "line: " << line << std::endl;
			//std::cout << "hit" << std::endl;
			if (it->second == tagnumber)
			{
				hit++;
			}
			else
			{
				miss++;
				cache.at(linenumber) = (tagnumber);
			}
}
void direct_cache::print()
{
	/*
	for (int i = 0; i < cache.size(); i++)
	{
		std::cout << cache.at(i) << std::endl;
	}
	*/
	hitrate = (float)hit / (float)(hit + miss);

	std::cout << "hit: " << hit << std::endl;
	std::cout << "miss: " << miss << std::endl;
	std::cout << "hit rate: " << hitrate << std::endl;
	std::cout << std::endl;
}

class set_cache
{
public:
	void populate(int, int, int, std::string, int);
	void initialize_cache(int,int);
	void print();

	struct set
	{
		//every line has:
		//a tag
		//a counter
		std::vector<std::pair<int,int>> lines;
	};
	
private:
	int hit = 0;
	int miss = 0;
	float hitrate = 0;
	//create a map
	//use set number as the key
	//use the actual set object as the value
	
	//the lines should be the actual tag followed by the counter
	std::map<int, set*> cache;
	int biggest = 0;

};
void set_cache::initialize_cache(int numberoflines, int linesperset)
{
	int numberofsets = numberoflines / linesperset;
	if (cache.size() > 0)
	{
		cache.clear();
	}
	for (int i = 0; i < numberofsets; i++)
	{
		set* s = new set;
		for (int i = 0; i < linesperset; i++)
		{
			s->lines.push_back(std::make_pair(0,0));
		}
		cache.emplace(i,s);
	}
	counter = 1;
	slots = 0;
	hit = 0;
	miss = 0;
}
void set_cache::populate(int bytesinline, int numberoflines, int linesinset, std::string address, int policy)
{
	int offsetwidth = ceil(log2(bytesinline));
	int setwidth = log2(ceil(numberoflines / linesinset));
	int tagwidth = address.size() - offsetwidth - setwidth;
	std::string tag = address.substr(0, tagwidth);
	std::string offset = address.substr(tagwidth + setwidth, offsetwidth);
	std::string set = address.substr(tagwidth, setwidth);
	//int index = setnum * linesinset; //first index of our set
	bool hitted = false;
	int lowest = counter;
	int tagnumber = bintoint(tag);
	int setnumber = bintoint(set);

	//iterate through entire set and find our value
		auto it = cache.find(setnumber);
		for (int i = 0; i < linesinset; i++)
		{
			if (it->second->lines.at(i).first == tagnumber)
			{
				if (policy == 0)
				{
					counter++;
					it->second->lines.at(i).second = counter;
				}
				hit++;
				hitted = true;
				break;
			}
		}
		//if hit is equal to false
		//iterate through our set
		// find out which ones are full
		//if set is full ,iterate again and find which value has the lesser counter value
		//iterate again, increment counter, and perform a replacement
		//our data doesnt exist,we need to add it.
		if (hitted == false)
		{
			miss++;
			counter++;
			int temp = 0;
			//determine if were full
			for (int i = 0; i < it->second->lines.size(); i++)
			{
				if (it->second->lines.at(i).first != 0)
				{
					temp++;
				}
			}
			//if were not full
			if (temp != it->second->lines.size())
			{
				//replace
				for (int i = 0; i < it->second->lines.size(); i++)
				{
					//we have an empty spot
					if (it->second->lines.at(i).first == 0)
					{
						it->second->lines.at(i).first = tagnumber;
						it->second->lines.at(i).second = counter;
						break;
					}
				}
			}
			//were full
			else if (temp == it->second->lines.size())
			{
				//find lowest counter data
				for (int i = 0; i < it->second->lines.size(); i++)
				{
					if (it->second->lines.at(i).second < lowest)
					{
						lowest = it->second->lines.at(i).second;
					}
				}

				//perform our replacement
				for (int i = 0; i < it->second->lines.size(); i++)
				{
					if (it->second->lines.at(i).second == lowest)
					{
						it->second->lines.at(i).first = tagnumber;
						it->second->lines.at(i).second = counter;
						break;
					}
				}
			}
		}
		
}
	
void set_cache::print()
{
	/*
	for (int i = 0; i < cache.size(); i++)
	{
		for (int j = 0; j < cache.at(i)->lines.size(); j++)
		{
			std::cout << "set: " << i << " tag: " << cache.at(i)->lines.at(j).first << std::endl;
		}
	}
	*/
	hitrate = (float)hit / (float)(hit + miss);
	std::cout << "hit: " << hit << std::endl;
	std::cout << "miss: " << miss << std::endl;
	std::cout << "hit rate: " << hitrate << std::endl;
	std::cout << std::endl;
}
class fully_cache
{
public:
	void populate(int, int, std::string,int);
	void initialize_cache(int);
	void print();
	struct obj
	{
		int tag = 0;
		int count = 0;
		//iterate through whole thing and find tag
		//if you hit the tag, thats fine.
		//if you dont hit the tag, we need to add it in there by finding extra spae
		//if there is no extra space, make some with counter method.
	};
private:
	int hit = 0;
	int miss = 0;
	float hitrate = 0;
	int biggest = 0;
	int taken = 0;
	std::vector<obj*> cache;
};
void fully_cache::initialize_cache(int numberoflines)
{
	if (cache.size() > 0)
	{
		cache.clear();
	}
	for (int i = 0; i < numberoflines; i++)
	{
		obj* j = new obj;
		j->tag = 0;
		j->count = 0;
		cache.push_back(j);
	}
	counter = 0;
	slots = 0;
	hit = 0;
	miss = 0;
}
void fully_cache::populate(int bytesinline, int numberoflines, std::string address, int policy)
{
	//this SHOULD get rid of A4 and replace it with A3
	int offsetwidth = ceil(log2(bytesinline));
	int linewidth = ceil(log2(numberoflines));
	int tagwidth = address.size() - offsetwidth - linewidth;
	std::string tag = address.substr(0, tagwidth);
	bool hitted = false;
	int lowest = counter;
	int tagnumber = bintoint(tag);

	//iterate and see if we have the data
	for (int i = 0; i < cache.size(); i++)
	{
		if (cache.at(i)->tag == tagnumber)
		{
			if (policy == 0)
			{
				counter++;
				cache.at(i)->count = counter;
			}
			hit++;
			counter++;
			hitted = true;
			break;
		}
	}
	//our data doesnt exist,we need to add it.
	if (hitted == false)
	{
		miss++;
		counter++;
		//if were not full
		if (taken != cache.size())
		{
			//replace
			for (int i = 0; i < cache.size(); i++)
			{
				//we have an empty spot
				if (cache.at(i)->tag == 0)
				{
					cache.at(i)->tag = tagnumber;
					cache.at(i)->count = counter;
					taken++;
					break;
				}
			}
		}
		//were full
		else if (taken == cache.size())
		{
			//find lowest counter data
			for (int i = 0; i < cache.size(); i++)
			{
				if (cache.at(i)->count < lowest)
				{
					lowest = cache.at(i)->count;
				}
			}

			//perform our replacement
			for (int i = 0; i < cache.size(); i++)
			{
				if (cache.at(i)->count == lowest)
				{
					cache.at(i)->tag = tagnumber;
					cache.at(i)->count = counter;
					break;
				}
			}
		}
	}
}

	
void fully_cache::print()
{
	/*
	for (int i = 0; i < cache.size(); i++)
	{
		std::cout << cache.at(i)->tag << std::endl;
	}
	*/
	hitrate = (float)hit / (float)(hit + miss);
	std::cout << "hit: " << hit << std::endl;
	std::cout << "miss: " << miss << std::endl;
	std::cout << "hit rate: " << hitrate << std::endl;
	std::cout << std::endl;
}

