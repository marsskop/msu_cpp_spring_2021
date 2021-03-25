#ifndef ALLOCATOR_H
#define ALLOCATOR_H


class Allocator {
public:
	Allocator(): offset(nullptr), base(nullptr), totalSize(size_t(0)) {};
	~Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    char* baseAddress() const;
    void reset();
private:
    char* offset;
    char* base;
    size_t totalSize{};
};


#endif //ALLOCATOR_H
