#include "DeSerializer.h"

struct Data {
	uint64_t a;
	bool b;
	uint64_t c;
	template <class Serializer> Error serialize(Serializer& serializer) {
		return serializer(a, b, c);
	}
};

void DefaultTest() {
	Data x { 1, true, 2 };
	std::stringstream stream;
	Serializer serializer(stream);
	serializer.save(x);

	Data y { 0, false, 0 };
	Deserializer deserializer(stream);
	const Error err = deserializer.load(y);

	assert(err == Error::NoError);
	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);
}

void CorruptTest() {
	Data x {1, true, 2};
	std::stringstream stream;
	stream << "12 a 34";
	Deserializer deserializer(stream);
	const Error err = deserializer.load(x);

	assert(err == Error::CorruptedArchive);
	assert(x.a == 12);
	assert(x.b == true);
	assert(x.c == 2);
}

int main() {
	DefaultTest();
	CorruptTest();
	std::cout << "Success!" << std::endl;
	return 0;
}