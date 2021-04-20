CC=g++ -std=c++17

all: main.cpp DeSerializer.cpp DeSerializer.h
	$(CC) main.cpp DeSerializer.cpp -o main

test: main.cpp DeSerializer.cpp DeSerializer.h
	$(CC) main.cpp DeSerializer.cpp -o test
	./test