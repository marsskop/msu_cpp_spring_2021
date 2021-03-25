#include <iostream>
#include <cassert>
#include "Allocator.h"

void DefaultTest(){
	Allocator CustomAllocator;
	CustomAllocator.makeAllocator(1024);
	char* p1 = CustomAllocator.alloc(500);
	char* p2 = CustomAllocator.alloc(500);
	char* p3 = CustomAllocator.alloc(100);
	CustomAllocator.reset();
	char* p4 = CustomAllocator.alloc(100);
	assert(p1 && p2 && !p3 && p4);
}

void AllocBefore(){
	Allocator CustomAllocator;
	char* p1 = CustomAllocator.alloc(200);
	assert(!p1);
}

void FewAllocators(){
	Allocator CustomAllocator;
	CustomAllocator.makeAllocator(1024);
	char* ad1 = CustomAllocator.baseAddress();
	CustomAllocator.makeAllocator(1024);
	char* ad2 = CustomAllocator.baseAddress();
	assert(ad1 == ad2);
}

int main() {
    DefaultTest();
	AllocBefore();
	FewAllocators();
	std::cout << "Success!" << std::endl;
    return 0;
}
