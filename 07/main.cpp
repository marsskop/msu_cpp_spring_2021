#include "Vector.h"

void CreationTest() {
	Vector<int> vec1(10);
	assert(vec1.size() == 0);
	assert(vec1.capacity() == 10);

	Vector<int> vec2(10, 1);
	assert(vec2.size() == 10);
	assert(vec2.capacity() == 10);
	for (size_t i=0; i != 10; i++) {
		assert(vec2[i] == 1);
	}

	Vector <int> vec3(vec2);
	assert(vec3.size() == 10);
	assert(vec3.capacity() == 10);
	for (size_t i=0; i != 10; i++) {
		assert(vec3[i] == 1);
	}
}

void CapacityTest() {
	Vector<int> vec(10, -1);
	assert(!vec.empty());
	assert(vec.size() == 10);
	assert(vec.capacity() == 10);

	vec.pop_back();
	assert(vec.size() == 9);
	assert(vec.capacity() == 10);

	vec.resize(10);
	assert(vec.size() == 10);
	assert(vec.capacity() == 10);

	vec.resize(11);
	assert(vec.size() == 11);
	assert(vec.capacity() == 16);

	vec.push_back(-1);
	assert(vec.size() == 12);
	assert(vec.capacity() == 16);

	vec.reserve(20);
	assert(vec.size() == 12);
	assert(vec.capacity() == 20);

	vec.reserve(10);
	assert(vec.size() == 12);
	assert(vec.capacity() == 20);

	vec.resize(1);
	assert(vec.size() == 1);
	assert(vec.capacity() == 20);

	vec.resize(0);
	assert(vec.size() == 0);
	assert(vec.empty());
	assert(vec.capacity() == 20);
}

void ModifiersTest() {
	Vector<int> vec(10, 1);
	assert(vec.size() == 10);
	for (size_t i=0; i != 10; i++) {
		assert(vec[i] == 1);
	}

	vec.pop_back();
	vec.pop_back();
	assert(vec.size() == 8);
	for (size_t i=0; i != 8; i++) {
		assert(vec[i] == 1);
	}

	vec.push_back(2);
	assert(vec.size() == 9);
	for (size_t i=0; i != 8; i++) {
		assert(vec[i] == 1);
	}
	assert(vec[8] == 2);

	vec.emplace_back(3);
	assert(vec.size() == 10);
	for (size_t i=0; i != 8; i++) {
		assert(vec[i] == 1);
	}
	assert(vec[8] == 2);
	assert(vec[9] == 3);

	vec.clear();
	assert(vec.size() == 0);
}

void IteratorTest() {
	Vector<int> vec(5, 1);
	std::for_each(vec.begin(), vec.end(), [](int x) {assert(x == 1);});

	vec.push_back(2);
	auto res1 = std::find(vec.begin(), vec.end(), 1);
	auto res2 = std::find(vec.begin(), vec.end(), 2);
	auto res3 = std::find(vec.begin(), vec.end(), 3);
	assert(res1 == vec.begin());
	assert(res2 == vec.end()-1);
	assert(res3 == vec.end());

	auto res11 = std::find(vec.rbegin(), vec.rend(), 2);
	auto res21 = std::find(vec.rbegin(), vec.rend(), 3);
	assert(res11 == vec.rbegin());
	assert(res21 == vec.rend());

	vec.pop_back();
	std::for_each(vec.rbegin(), vec.rend(), [](int x) {assert(x == 1);});
}

int main() {
	CreationTest();
	CapacityTest();
	ModifiersTest();
	IteratorTest();
	std::cout << "Success!" << std::endl;
}