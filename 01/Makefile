CC=g++ -std=c++17

all: main.cpp Allocator.cpp Allocator.h
	$(CC) main.cpp Allocator.cpp -o main

test: main.cpp Allocator.cpp Allocator.h
	$(CC) main.cpp Allocator.cpp -o test
	./test

clean:
	del allocator.exe