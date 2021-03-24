CC=g++ -std=c++17

all: test

test: main.cpp Allocator.cpp Allocator.h
	$(CC) main.cpp Allocator.cpp -o allocator

clean:
	del allocator.exe