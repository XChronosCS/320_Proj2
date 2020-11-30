#ifndef DIRECT_MAP_H
#define DIRECT_MAP_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <queue>

struct CacheLine {
	int valid = 0;
	unsigned long tag;
};

class DirectMap {
private:
	const int BLOCK_SIZE = 32;
	const int OFFSET_SIZE = 5;
	unsigned long num_blocks;
	unsigned long accesses_performed;
	unsigned long cache_hits;
	CacheLine* cache_table;
public:
	DirectMap(unsigned long);
	~DirectMap();
	void cache_operation(unsigned long long address);
	unsigned long getAccesses() {
		return this->accesses_performed;
	}
	unsigned long getHits() {
		return this->cache_hits;
	}
};
#endif
