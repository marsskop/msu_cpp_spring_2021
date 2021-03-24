#include <iostream>
#include <cassert>
#include "Allocator.h"

int main() {
    Allocator CustomAllocator;
    try{
        CustomAllocator.makeAllocator(1024);
    }
    catch (const char* str){
        std::cout << str << std::endl;
    }
    std::cout << "Testing..." << std::endl;
    char* p1 = CustomAllocator.alloc(500);
    char* p2 = CustomAllocator.alloc(500);
    char* p3 = CustomAllocator.alloc(100);
    assert(p1 && p2 && !p3);
    CustomAllocator.reset();
    char* p4 = CustomAllocator.alloc(100);
    assert(p4);

    return 0;
}
