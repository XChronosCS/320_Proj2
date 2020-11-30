#include "SetAssoc.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>


SetAssoc::SetAssoc(unsigned long sets) : accesses_performed(0), cache_hits(0)
{
	this->num_sets = this->NUM_BLOCKS / sets;
	this->blocks_per_set = sets;
	this->set_table = new Set[this->num_sets];
}

SetAssoc::~SetAssoc()
{
	delete[] this->set_table;
}

void SetAssoc::set_operation(unsigned long long address)
{
	unsigned long long addr = address / this->BLOCK_SIZE; //Gets rid of offset
	unsigned long index = addr % this->num_sets;
	unsigned long tag = addr / this->num_sets;
	bool need_replace = false;
	Set* checked_set = &(this->set_table[index]);
	for (unsigned long i = 0; i < this->blocks_per_set; i++) {
		SetLine* checked_line = &(checked_set->blocks[i]);
		if (checked_line->valid == 0) {
			checked_line->valid = 1;
			checked_line->tag = tag;
			checked_set->LRU_Order.push(i);
			break;
		}
		if (checked_line->tag == tag) {
			this->cache_hits++;
			checked_set->LRU_Order.remove(i);
			checked_set->LRU_Order.push(i);
			break;
		}
		if (i == this->blocks_per_set - 1) {
			need_replace = true;
		}
	}
	if (need_replace) {
		int last_used = checked_set->LRU_Order.front();
		checked_set->LRU_Order.pop();
		SetLine* rep_line = &(checked_set->blocks[last_used]);
		rep_line->tag = tag;
		checked_set->LRU_Order.push(last_used);
	}
	this->accesses_performed++;
}

NoAlloc::NoAlloc(unsigned long sets) : accesses_performed(0), cache_hits(0)
{
	this->num_sets = this->NUM_BLOCKS / sets;
	this->blocks_per_set = sets;
	this->set_table = new Set[this->num_sets];
}

NoAlloc::~NoAlloc()
{
	delete[] this->set_table;
}

void NoAlloc::set_operation(unsigned long long address, char op)
{
	unsigned long long addr = address / this->BLOCK_SIZE; //Gets rid of offset
	unsigned long index = addr % this->num_sets;
	unsigned long tag = addr / this->num_sets;
	bool need_replace = false;
	Set* checked_set = &(this->set_table[index]);
	for (unsigned long i = 0; i < this->blocks_per_set; i++) {
		SetLine* checked_line = &(checked_set->blocks[i]);
		if (checked_line->valid == 0 && op != this->STORE) {
			checked_line->valid = 1;
			checked_line->tag = tag;
			checked_set->LRU_Order.push(i);
			break;
		}
		if (checked_line->tag == tag) {
			this->cache_hits++;
			checked_set->LRU_Order.remove(i);
			checked_set->LRU_Order.push(i);
			break;
		}
		if (i == this->blocks_per_set - 1) {
			need_replace = true;
		}
	}
	if (need_replace && op != this->STORE) {
		int last_used = checked_set->LRU_Order.front();
		checked_set->LRU_Order.pop();
		SetLine* rep_line = &(checked_set->blocks[last_used]);
		rep_line->tag = tag;
		checked_set->LRU_Order.push(last_used);
	}
	this->accesses_performed++;
}

PrefetchAlways::PrefetchAlways(unsigned long sets) : accesses_performed(0), cache_hits(0)
{
	this->num_sets = this->NUM_BLOCKS / sets;
	this->blocks_per_set = sets;
	this->set_table = new Set[this->num_sets];
}

PrefetchAlways::~PrefetchAlways()
{
	delete[] this->set_table;
}

void PrefetchAlways::set_operation(unsigned long long address_base)
{
	bool hit_check = false;
	unsigned long long addresses[2] = { address_base, address_base + 32 };
	for (int j = 0; j < 2; j++) {
		unsigned long long addr = addresses[j] / this->BLOCK_SIZE; //Gets rid of offset
		unsigned long index = addr % this->num_sets;
		unsigned long tag = addr / this->num_sets;
		bool need_replace = false;
		Set* checked_set = &(this->set_table[index]);
		for (unsigned long i = 0; i < this->blocks_per_set; i++) {
			SetLine* checked_line = &(checked_set->blocks[i]);
			if (checked_line->valid == 0) {
				checked_line->valid = 1;
				checked_line->tag = tag;
				checked_set->LRU_Order.push(i);
				break;
			}
			if (checked_line->tag == tag) {
				if (j == 0) { hit_check = true; }
				checked_set->LRU_Order.remove(i);
				checked_set->LRU_Order.push(i);
				break;
			}
			if (i == this->blocks_per_set - 1) {
				need_replace = true;
			}
		}
		if (need_replace) {
			int last_used = checked_set->LRU_Order.front();
			checked_set->LRU_Order.pop();
			SetLine* rep_line = &(checked_set->blocks[last_used]);
			rep_line->tag = tag;
			checked_set->LRU_Order.push(last_used);
		}
	}
	if (hit_check) { this->cache_hits++; }
	this->accesses_performed++;
}


MissPrefetch::MissPrefetch(unsigned long sets) : accesses_performed(0), cache_hits(0)
{
	this->num_sets = this->NUM_BLOCKS / sets;
	this->blocks_per_set = sets;
	this->set_table = new Set[this->num_sets];
}

MissPrefetch::~MissPrefetch()
{
	delete[] this->set_table;
}

void MissPrefetch::set_operation(unsigned long long address_base)
{
	bool hit_check = false;
	unsigned long long addresses[2] = { address_base, address_base + 32 };
	bool cache_miss = true;
	for (int j = 0; j < 2; j++) {
		if (cache_miss) {
			unsigned long long addr = addresses[j] / this->BLOCK_SIZE; //Gets rid of offset
			unsigned long index = addr % this->num_sets;
			unsigned long tag = addr / this->num_sets;
			bool need_replace = false;
			Set* checked_set = &(this->set_table[index]);
			for (unsigned long i = 0; i < this->blocks_per_set; i++) {
				SetLine* checked_line = &(checked_set->blocks[i]);
				if (checked_line->valid == 0) {
					checked_line->valid = 1;
					checked_line->tag = tag;
					checked_set->LRU_Order.push(i);
					break;
				}
				if (checked_line->tag == tag) {
					if (j == 0) { hit_check = true; }
					checked_set->LRU_Order.remove(i);
					checked_set->LRU_Order.push(i);
					cache_miss = false;
					break;
				}
				if (i == this->blocks_per_set - 1) {
					need_replace = true;
				}
			}
			if (need_replace) {
				int last_used = checked_set->LRU_Order.front();
				checked_set->LRU_Order.pop();
				SetLine* rep_line = &(checked_set->blocks[last_used]);
				rep_line->tag = tag;
				checked_set->LRU_Order.push(last_used);
			}
		}
	}
	if (hit_check) { this->cache_hits++; }
	this->accesses_performed++;
}

