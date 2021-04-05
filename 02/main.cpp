#include "TokenParser.h"

void DefaultTest() {
	std::vector<std::string> strcheck;
	std::vector<std::uint64_t> numcheck;
	startendcall start_callback = [](){std::cout << "DefaultTest start" << std::endl;};
	startendcall end_callback = [](){std::cout << "DefaultTest end" << std::endl;};
	digitcall digit_callback = [&](std::uint64_t num){
		numcheck.push_back(num);
		std::cout << num << std::endl;
	};
	stringcall string_callback = [&](const std::string& str){
		strcheck.push_back(str);
		std::cout << str << std::endl;
	};

	std::string input("auf     dedinsid8 1234 567\t\nTHIS*** 112\r3a3bb 1 a");
	TokenParser CustomParser;
	CustomParser.SetStartCallback(start_callback);
	CustomParser.SetEndCallback(end_callback);
	CustomParser.SetDigitTokenCallback(digit_callback);
	CustomParser.SetStringTokenCallback(string_callback);

	CustomParser.Parse(input);

	std::vector<std::string> strans = {"auf", "dedinsid8", "THIS***", "3a3bb", "a"};
	std::vector<std::uint64_t> numans = {1234, 567, 112, 1};
	for (int i=0; i < strans.size(); i++) {
		assert(strans[i] == strcheck[i]);
	}
	for (int i=0; i < numans.size(); i++) {
		assert(numans[i] == numcheck[i]);
	}
}

void StartEndCallbacks() {
	bool start_call = false;
	bool end_call = false;
	startendcall start_callback = [&](){
		start_call = true;
		std::cout << "Start callback" << std::endl;
	};
	startendcall end_callback = [&](){
		end_call = true;
		std::cout << "End callback" << std::endl;
	};

	std::string input("djkdks ddkd 9202 2id0");
	TokenParser CustomParser;
	CustomParser.SetStartCallback(start_callback);
	CustomParser.SetEndCallback(end_callback);

	CustomParser.Parse(input);

	assert(start_call && end_call);
}

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

void BigNum() {
	std::vector<std::string> nums;
	digitcall digit_callback = [&](std::uint64_t num){
		nums.push_back(std::to_string(num));
		std::cout << num << std::endl;
	};
	stringcall string_callback = [&](const std::string& str){
		std::cout << str << std::endl;
	};

	std::string input("18446744073709551615   18446744073709551616");
	TokenParser CustomParser;
	CustomParser.SetDigitTokenCallback(digit_callback);
	CustomParser.SetStringTokenCallback(string_callback);

	CustomParser.Parse(input);

	std::vector<std::string> ans = {"18446744073709551615"};
	for (int i=0; i < ans.size(); i++) {
		assert(ans[i] == nums[i]);
	}
}

void EmptyInput() {
	bool digit_call = false;
	bool string_call = false;
	digitcall digit_callback = [&](std::uint64_t num){
		digit_call = true;
		std::cout << num << std::endl;
	};
	stringcall string_callback = [&](const std::string& str){
		string_call = true;
		std::cout << str << std::endl;
	};

	std::string input("");
	TokenParser CustomParser;
	CustomParser.SetDigitTokenCallback(digit_callback);
	CustomParser.SetStringTokenCallback(string_callback);

	CustomParser.Parse(input);

	assert(!digit_call && !string_call);
}

void SpacesInput() {
	bool digit_call = false;
	bool string_call = false;
	digitcall digit_callback = [&](std::uint64_t num) {
		digit_call = true;
		std::cout << num << std::endl;
	};
	stringcall string_callback = [&](const std::string &str) {
		string_call = true;
		std::cout << str << std::endl;
	};

	std::string input("   ");
	TokenParser CustomParser;
	CustomParser.SetDigitTokenCallback(digit_callback);
	CustomParser.SetStringTokenCallback(string_callback);

	CustomParser.Parse(input);

	assert(!digit_call && !string_call);
}

int main() {
	DefaultTest();
	StartEndCallbacks();
	NoCallbacks();
	BigNum();
	EmptyInput();
	SpacesInput();
	std::cout << "Success!" << std::endl;
	return 0;
}