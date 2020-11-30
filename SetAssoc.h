#ifndef SET_ASSOC_H
#define SET_ASSOC_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <queue>
#include <list>

struct SetLine {
	int valid = 0;
	unsigned long tag;
};

class Queue : public std::queue<unsigned long, std::list<unsigned long>> {
public:
	void remove(unsigned long var) {
		this->c.remove(var);
	}
};
struct Set {
	Queue LRU_Order;
	SetLine blocks[16];
};

class SetAssoc {
private:
	const int BLOCK_SIZE = 32;
	const int OFFSET_SIZE = 5;
	const int SIZE_CACHE = 16384;
	const unsigned long NUM_BLOCKS = 512;
	unsigned long blocks_per_set;
	unsigned long accesses_performed;
	unsigned long cache_hits;
	Set* set_table;
	unsigned long num_sets;
public:
	SetAssoc(unsigned long);
	~SetAssoc();
	void set_operation(unsigned long long);
	unsigned long getAccesses() {
		return this->accesses_performed;
	}
	unsigned long getHits() {
		return this->cache_hits;
	}
};

class NoAlloc {
private:
	const int BLOCK_SIZE = 32;
	const int OFFSET_SIZE = 5;
	const int SIZE_CACHE = 16384;
	const char STORE = 'S';
	const unsigned long NUM_BLOCKS = 512;
	unsigned long blocks_per_set;
	unsigned long accesses_performed;
	unsigned long cache_hits;
	Set* set_table;
	unsigned long num_sets;
public:
	NoAlloc(unsigned long);
	~NoAlloc();
	void set_operation(unsigned long long, char);
	unsigned long getAccesses() {
		return this->accesses_performed;
	}
	unsigned long getHits() {
		return this->cache_hits;
	}
};

class PrefetchAlways {
private:
	const int BLOCK_SIZE = 32;
	const int OFFSET_SIZE = 5;
	const int SIZE_CACHE = 16384;
	const unsigned long NUM_BLOCKS = 512;
	unsigned long blocks_per_set;
	unsigned long accesses_performed;
	unsigned long cache_hits;
	Set* set_table;
	unsigned long num_sets;
public:
	PrefetchAlways(unsigned long);
	~PrefetchAlways();
	void set_operation(unsigned long long);
	unsigned long getAccesses() {
		return this->accesses_performed;
	}
	unsigned long getHits() {
		return this->cache_hits;
	}
};

class MissPrefetch {
private:
	const int BLOCK_SIZE = 32;
	const int OFFSET_SIZE = 5;
	const int SIZE_CACHE = 16384;
	const unsigned long NUM_BLOCKS = 512;
	unsigned long blocks_per_set;
	unsigned long accesses_performed;
	unsigned long cache_hits;
	Set* set_table;
	unsigned long num_sets;
public:
	MissPrefetch(unsigned long);
	~MissPrefetch();
	void set_operation(unsigned long long);
	unsigned long getAccesses() {
		return this->accesses_performed;
	}
	unsigned long getHits() {
		return this->cache_hits;
	}
};


#endif
#pragma once
