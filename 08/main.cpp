#include "ThreadPool.h"

int f1(int& a) {
	a *= 10;
	return a;
}

int f2(int& a) {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	a++;
	return a;
}

int f3(int& a, int b, int c) {
	a += b + c;
	std::this_thread::sleep_for(std::chrono::milliseconds(0));
	return a;
}

int f4(int& a, std::string b) {
	int _ = f2(a);
	a += b.length();
	return a;
}

void DefaultTest() {
	ThreadPool pool(8);
	int a = 1;

	auto task1 = pool.exec(f1, a);
	int test1 = task1.get();
	auto task2 = pool.exec(f2, a);
	int test2 = task2.get();

	assert(a == 1);
	assert(test1 == 10);
	assert(test2 == 2);

	auto task3 = pool.exec(f2, std::ref(a));
	int test3 = task3.get();
	auto task4 = pool.exec(f1, std::ref(a));
	int test4 = task4.get();

	assert(a == 20);
	assert(test3 == 2);
	assert(test4 == 20);

	auto task5 = pool.exec(f3, std::ref(a), 1, 2);
	int test5 = task5.get();

	assert(a == 23);
	assert(test5 == 23);

	auto task6 = pool.exec(f4, a, "random string");
	int test6 = task6.get();

	assert(a == 23);
	assert(test6 == 37);
}

int main() {
	DefaultTest();
	std::cout << "Success!" << std::endl;
	return 0;
}

