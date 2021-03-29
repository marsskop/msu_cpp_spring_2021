#include "TokenParser.h"

void NoCallbacks() {
	std::string input("auf     dedinsid8 1234 567\t\nTHIS*** 112\r33");
	bool noexception = true;
	TokenParser CustomParser;
	try {
		CustomParser.Parse(input);
	}
	catch(...) {
		noexception = false;
	}
	assert(noexception);
}
void DefaultTest() {
	std::vector<std::string> check;
	startendcall start_callback = [](){std::cout << "DefaultTest start" << std::endl;};
	startendcall end_callback = [](){std::cout << "DefaultTest end" << std::endl;};
	digitcall digit_callback = [&](int num){
		check.push_back(std::to_string(num));
		std::cout << num << std::endl;
	};
	stringcall string_callback = [&](const std::string& str){
		check.push_back(str);
		std::cout << str << std::endl;
	};

	std::string input("auf     dedinsid8 1234 567\t\nTHIS*** 112\r3a3bb");
	TokenParser CustomParser;
	CustomParser.SetStartCallback(start_callback);
	CustomParser.SetEndCallback(end_callback);
	CustomParser.SetDigitTokenCallback(digit_callback);
	CustomParser.SetStringTokenCallback(string_callback);

	CustomParser.Parse(input);

	std::vector<std::string> ans = {"auf", "dedinsid8", "1234", "567", "THIS***", "112", "3a3bb"};
	for (int i=0; i < ans.size(); i++) {
		assert(ans[i] == check[i]);
	}
}

int main() {
	DefaultTest();
	NoCallbacks();
	std::cout << "Success!" << std::endl;
	return 0;
}