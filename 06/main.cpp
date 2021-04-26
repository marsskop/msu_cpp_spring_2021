#include "format.h"

void DefaultTest() {
	auto text = format("{1}+{1} = {0}", 2, "one");
	assert(text == "one+one = 2");
}

void EmptyTest() {
	auto text = format("");
	assert(text == "");
}

void WrongInputTest() {
	std::string except;
	try {
		auto text = format("{1abcd}", 2);
	}
	catch (Error& ex) {
		except = ex.message_;
	}
	assert(except == "Not a number met inside brackets");

	try {
		auto text = format("{}", 2);
	}
	catch (Error& ex) {
		except = ex.message_;
	}
	assert(except == "No number in brackets");

	try {
		auto text = format("{1}", 2);
	}
	catch (Error& ex) {
		except = ex.message_;
	}
	assert(except == "Number in brackets is too large");

	try {
		auto text = format("{0", 2);
	}
	catch (Error& ex) {
		except = ex.message_;
	}
	assert(except == "End of string before closing brackets");

	try {
		auto text = format("}{0}", 2);
	}
	catch (Error& ex) {
		except = ex.message_;
	}
	assert(except == "Closing bracket before opening one");
}

int main() {
	DefaultTest();
	EmptyTest();
	WrongInputTest();
	std::cout << "Success!" << std::endl;
	return 0;
}