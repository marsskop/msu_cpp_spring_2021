CC=g++ -std=c++17

all: main.cpp ThreadPool.h
	$(CC) main.cpp -lpthread -o main

test: main.cpp ThreadPool.h
	$(CC) main.cpp -lpthread -o test
	./test
