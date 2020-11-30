#include "FullAssoc.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>



FullAssoc::FullAssoc() : accesses_performed(0), cache_hits(0)
{
	this->block_table = new BlockLine[this->NUM_BLOCKS];
}

FullAssoc::~FullAssoc()
{
	delete[] this->block_table;
}

void FullAssoc::set_operation(unsigned long long address)
{
	unsigned long tag = address / this->BLOCK_SIZE; //Gets rid of offset
	bool need_replace = false;
	for (unsigned long i = 0; i < this->NUM_BLOCKS; i++) {
		BlockLine* checked_line = &(this->block_table[i]);
		if (checked_line->valid == 0) {
			checked_line->valid = 1;
			checked_line->tag = tag;
			this->LRU_Order.push(i);
			break;
		}
		if (checked_line->tag == tag) {
			this->cache_hits++;
			this->LRU_Order.remove(i);
			this->LRU_Order.push(i);
			break;
		}
		if (i == this->NUM_BLOCKS - 1) {
			need_replace = true;
		}
	}
	if (need_replace) {
		int last_used = this->LRU_Order.front();
		this->LRU_Order.pop();
		BlockLine* rep_line = &(this->block_table[last_used]);
		rep_line->tag = tag;
		this->LRU_Order.push(last_used);
	}
	this->accesses_performed++;
}

HotCold::HotCold() : accesses_performed(0), cache_hits(0)
{
	this->block_table = new BlockLine[this->NUM_BLOCKS];
}

HotCold::~HotCold()
{
	delete[] this->block_table;
}

unsigned long HotCold::traverse() 
{
	int i = 0;
	int index = 0;
	int offset_size = this->NUM_BLOCKS / 2;
	while (i < 511) {
		if (this->hot_cold_array[i] == 1) {
			i = ((2 * i) + 2);
			index += offset_size;
		}
		else {
			i = ((2 * i) + 1);
		}
		offset_size /= 2;
	}
	return index;
}

void HotCold::update(unsigned long index)
{
	unsigned long i = index + 511;
	unsigned long child;
	while (i > 0) {
		child = i;
		i = (i - 1) / 2;
		if ((2 * i) + 2 == child) {
			this->hot_cold_array[i] = 0;
		}
		else {
			this->hot_cold_array[i] = 1;
		}
		}
	
}

void HotCold::set_operation(unsigned long long address)
{
	unsigned long tag = address / this->BLOCK_SIZE; //Gets rid of offset
	bool need_replace = false;
		for (unsigned long i = 0; i < this->NUM_BLOCKS; i++) {
			BlockLine* checked_line = &(this->block_table[i]);
			if (checked_line->tag == tag) {
				this->cache_hits++;
				this->update(i);
				break;
			}
			if (i == this->NUM_BLOCKS - 1) {
				need_replace = true;
			}
		}
		if (need_replace) {
			unsigned long last_used = this->traverse();
			//printf("Last Used = %d\n", (int)last_used);
			BlockLine* rep_line = &(this->block_table[last_used]);
			if (rep_line->valid == 0) {
				rep_line->valid = 1;
				//printf("Currents hits = %d\n", (int)this->cache_hits);
			}
			rep_line->tag = tag; 
			this->update(last_used);
		}

	this->accesses_performed++;
}