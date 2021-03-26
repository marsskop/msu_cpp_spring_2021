#include <cstdlib>
#include "Allocator.h"
#include <iostream>

void Allocator::makeAllocator(size_t maxSize) {
	delete[] base;
	delete[] offset;
    base = new char[maxSize];
    if (!base){
        throw "Error";
    }
    else {
        offset = base;
        totalSize = maxSize;
    }
}

char* Allocator::alloc(size_t size) {
    if (!size){
        return nullptr;
    }
    if (!totalSize){
    	return nullptr;
    }
    char* newoffset = offset + size;
    if (newoffset > base + totalSize - 1){
        return nullptr;
    }
    offset = newoffset;
    char* ptr = offset - size;
    return ptr;
}

char* Allocator::baseAddress() const {
	return this->base;
}

void Allocator::reset() {
    offset = base;
}

Allocator::~Allocator() {
	delete[] base;
}