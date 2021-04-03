#include <iostream>
#include <string>
#include <cassert>
#include <functional>

#ifndef TOKENPARSER_H
#define TOKENPARSER_H

using startendcall = void(*)(void);
using digitcall = std::function<void(unsigned long long)>;
using stringcall = std::function<void(const std::string&)>;

class TokenParser {
public:
	TokenParser() = default;
	void Parse(const std::string& text);
	void SetStartCallback(startendcall callback);
	void SetEndCallback(startendcall callback);
	void SetDigitTokenCallback(digitcall callback);
	void SetStringTokenCallback(stringcall callback);
private:
	startendcall startcallback = nullptr;
	startendcall endcallback = nullptr;
	digitcall digitcallback = nullptr;
	stringcall stringcallback = nullptr;
};

#endif //TOKENPARSER_H