#ifndef ALLOCATOR_H
#define ALLOCATOR_H


class Allocator {
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
private:
    char* offset;
    char* base;
    size_t totalSize;
};


#endif //ALLOCATOR_H
