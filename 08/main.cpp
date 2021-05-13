#include "ThreadPool.h"

struct A {};
void foo(const A&) {}

void DefaultTest() {
	ThreadPool pool(8);

	auto task1 = pool.exec(foo, A());
	task1.get();

	auto task2 = pool.exec([]() { return 1; });
	task2.get();
}

int main() {
	DefaultTest();
	std::cout << "Success!" << std::endl;
	return 0;
}