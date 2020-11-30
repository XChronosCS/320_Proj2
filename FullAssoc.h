#ifndef FULL_ASSOC_H
#define FULL_ASSOC_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <queue>
#include <list>


class LRUQueue : public std::queue<unsigned long, std::list<unsigned long>> {
public:
	void remove(unsigned long var) {
		this->c.remove(var);
	}
};
struct BlockLine {
	int valid = 0;
	unsigned long tag;
};

class FullAssoc {
private:
	const int BLOCK_SIZE = 32;
	const int OFFSET_SIZE = 5;
	const int SIZE_CACHE = 16384;
	const unsigned long NUM_BLOCKS = 512;
	unsigned long accesses_performed;
	unsigned long cache_hits;
	LRUQueue LRU_Order;
	BlockLine* block_table;

public:
	FullAssoc();
	~FullAssoc();
	void set_operation(unsigned long long);
	unsigned long getAccesses() {
		return this->accesses_performed;
	}
	unsigned long getHits() {
		return this->cache_hits;
	}
};

class HotCold {
private:
	const int BLOCK_SIZE = 32;
	const int OFFSET_SIZE = 5;
	const int SIZE_CACHE = 16384;
	const unsigned long NUM_BLOCKS = 512;
	unsigned long cur_blocks = 0;
	unsigned long accesses_performed;
	unsigned long cache_hits;
	BlockLine* block_table;
	int hot_cold_array[511] = { 0 };
public:
	HotCold();
	~HotCold();
	unsigned long traverse();
	void update(unsigned long);
	void set_operation(unsigned long long);
	unsigned long getAccesses() {
		return this->accesses_performed;
	}
	unsigned long getHits() {
		return this->cache_hits;
	}
};


#endif
