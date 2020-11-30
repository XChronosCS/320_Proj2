#include<iostream>
#include<fstream>
#include<string>
#include "DirectMap.h"
#include "SetAssoc.h"
#include "FullAssoc.h"

int main(int argc, char* argv[]) {
	unsigned long long addr;
	char operation;
	char* input_file = argv[1];
	char* output_file = argv[2];
	std::ifstream input;
	input.open(input_file);
	std::ofstream output;
	output.open(output_file);
	DirectMap direct1K = DirectMap(1);
	DirectMap direct4K = DirectMap(4);
	DirectMap direct16K = DirectMap(16);
	DirectMap direct32K = DirectMap(32);
	SetAssoc Set2 = SetAssoc(2);
	SetAssoc Set4 = SetAssoc(4);
	SetAssoc Set8 = SetAssoc(8);
	SetAssoc Set16 = SetAssoc(16);
	FullAssoc LRU = FullAssoc();
	HotCold HC = HotCold();
	NoAlloc NSet2 = NoAlloc(2);
	NoAlloc NSet4 = NoAlloc(4);
	NoAlloc NSet8 = NoAlloc(8);
	NoAlloc NSet16 = NoAlloc(16);
	PrefetchAlways PSet2 = PrefetchAlways(2);
	PrefetchAlways PSet4 = PrefetchAlways(4);
	PrefetchAlways PSet8 = PrefetchAlways(8);
	PrefetchAlways PSet16 = PrefetchAlways(16);
	MissPrefetch MSet2 = MissPrefetch(2);
	MissPrefetch MSet4 = MissPrefetch(4);
	MissPrefetch MSet8 = MissPrefetch(8);
	MissPrefetch MSet16 = MissPrefetch(16);

	while (input >> operation >> std::hex >> addr) {
		direct1K.cache_operation(addr);
		direct4K.cache_operation(addr);
		direct16K.cache_operation(addr);
		direct32K.cache_operation(addr);
		Set2.set_operation(addr);
		Set4.set_operation(addr);
		Set8.set_operation(addr);
		Set16.set_operation(addr);
		LRU.set_operation(addr);
		HC.set_operation(addr);
		NSet2.set_operation(addr, operation);
		NSet4.set_operation(addr, operation);
		NSet8.set_operation(addr, operation);
		NSet16.set_operation(addr, operation);
		PSet2.set_operation(addr);
		PSet4.set_operation(addr);
		PSet8.set_operation(addr);
		PSet16.set_operation(addr);
		MSet2.set_operation(addr);
		MSet4.set_operation(addr);
		MSet8.set_operation(addr);
		MSet16.set_operation(addr);
	}
	output << direct1K.getHits() << "," << direct1K.getAccesses() << "; ";
	output << direct4K.getHits() << "," << direct4K.getAccesses() << "; ";
	output << direct16K.getHits() << "," << direct16K.getAccesses() << "; ";
	output << direct32K.getHits() << "," << direct32K.getAccesses() << ";" << std::endl;
	output << Set2.getHits() << "," << Set2.getAccesses() << "; ";
	output << Set4.getHits() << "," << Set4.getAccesses() << "; ";
	output << Set8.getHits() << "," << Set8.getAccesses() << "; ";
	output << Set16.getHits() << "," << Set16.getAccesses() << ";" << std::endl;
	output << LRU.getHits() << "," << LRU.getAccesses() << ";" << std::endl;
	output << HC.getHits() << "," << HC.getAccesses() << ";" << std::endl;
	output << NSet2.getHits() << "," << NSet2.getAccesses() << "; ";
	output << NSet4.getHits() << "," << NSet4.getAccesses() << "; ";
	output << NSet8.getHits() << "," << NSet8.getAccesses() << "; ";
	output << NSet16.getHits() << "," << NSet16.getAccesses() << ";" << std::endl;
	output << PSet2.getHits() << "," << PSet2.getAccesses() << "; ";
	output << PSet4.getHits() << "," << PSet4.getAccesses() << "; ";
	output << PSet8.getHits() << "," << PSet8.getAccesses() << "; ";
	output << PSet16.getHits() << "," << PSet16.getAccesses() << ";" << std::endl;
	output << MSet2.getHits() << "," << MSet2.getAccesses() << "; ";
	output << MSet4.getHits() << "," << MSet4.getAccesses() << "; ";
	output << MSet8.getHits() << "," << MSet8.getAccesses() << "; ";
	output << MSet16.getHits() << "," << MSet16.getAccesses() << ";" << std::endl;
	input.close();
	output.close();
	return 0;
}