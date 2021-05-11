#include "format.h"

void DefaultTest() {
	auto text = format("{1}+{1} = {0}", 2, "one");
	assert(text == "one+one = 2");

	text = format("{0}", "one");
	assert(text == "one");

	text = format("{0}{1}{0}{0}{1}", 1, "two");
	assert(text == "1two11two");

	text = format("{0}{1}{2}{3}{4} {5}  {6}{7}{8}{9}{10}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, "eleven");
	assert(text == "12345 6  78910eleven");
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
	catch (InvArgExcept& ex) {
		except = ex.what();
	}
	assert(except == "Not a number met inside brackets");

	try {
		auto text = format("{string}", 1);
	}
	catch (InvArgExcept& ex) {
		except = ex.what();
	}
	assert(except == "Not a number met inside brackets");

	try {
		auto text = format("{}", 2);
	}
	catch (InvArgExcept& ex) {
		except = ex.what();
	}
	assert(except == "No number in brackets");

	try {
		auto text = format("{1}", 2);
	}
	catch (InvArgExcept& ex) {
		except = ex.what();
	}
	assert(except == "Number in brackets is too large");

	try {
		auto text = format("{0", 2);
	}
	catch (DomExcept& ex) {
		except = ex.what();
	}
	assert(except == "End of string before closing brackets");

	try {
		auto text = format("}{0}", 2);
	}
	catch (DomExcept& ex) {
		except = ex.what();
	}
	assert(except == "Closing bracket before opening one");

	try {
		auto text = format("{0}{", 2);
	}
	catch (DomExcept& ex) {
		except = ex.what();
	}
	assert(except == "End of string before closing brackets");

	try {
		auto text = format("{0}", 1, 2);
	}
	catch (DomExcept& ex) {
		except = ex.what();
	}
	assert(except == "Excess of arguments");

	try {
		auto text = format("{{0}}", 1);
	}
	catch (InvArgExcept& ex) {
		except = ex.what();
	}
	assert(except == "Not a number met inside brackets");

	try {
		auto text = format("{0}}{1}", 1, 2);
	}
	catch (DomExcept& ex) {
		except = ex.what();
	}
	assert(except == "Closing bracket before opening one");

	try {
		auto text = format("{0}{}", 1, 2);
	}
	catch (InvArgExcept& ex) {
		except = ex.what();
	}
	assert(except == "No number in brackets");

	try {
		auto text = format("{18446744073709551616}", 0);
	}
	catch (InvArgExcept& ex) {
		except = ex.what();
	}
	assert(except == "Number in brackets is too large");
}

int main() {
	DefaultTest();
	EmptyTest();
	WrongInputTest();
	std::cout << "Success!" << std::endl;
	return 0;
}