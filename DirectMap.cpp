#include "DirectMap.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>

DirectMap::DirectMap(unsigned long size) : accesses_performed(0), cache_hits(0)
{
	this->num_blocks = (size * 1024) / this->BLOCK_SIZE;
	this->cache_table = new CacheLine[num_blocks];
}

DirectMap::~DirectMap()
{
	delete[] cache_table;
}

void DirectMap::cache_operation(unsigned long long address)
{
	unsigned long long addr = address / this->BLOCK_SIZE; //Gets rid of offset
	unsigned long index = addr % this->num_blocks;
	unsigned long tag = addr / this->num_blocks;
	CacheLine * checked_line = &(this->cache_table[index]);
	if (checked_line->valid == 0 || checked_line->tag != tag) {
		checked_line->valid = 1;
		checked_line->tag = tag;
	}
	else {
		this->cache_hits++;
	}
	this->accesses_performed++;
}
