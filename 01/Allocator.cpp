#include <cstdlib>
#include "Allocator.h"

void Allocator::makeAllocator(size_t maxSize) {
    base = (char*) std::malloc(maxSize);
    if (base == nullptr){
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
    char* newoffset = offset + size;
    if (newoffset > base + totalSize - 1){
        return nullptr;
    }
    offset = newoffset;
    char* ptr = offset - size;
    return ptr;
}

void Allocator::reset() {
    offset = base;
}