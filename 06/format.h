#ifndef FORMATTER_H
#define FORMATTER_H

#include <iostream>
#include <cstring>
#include <sstream>
#include <cassert>
#include <exception>
#include <vector>

struct Error {
	std::string message_;
	const char* fileName_;
	int line_;
	Error(const std::string& message, const char* fileName, int line)
	: message_(message), fileName_(fileName), line_(line) {}
};

void convert_to_vec(std::vector<std::string>& args_vec) {
	return;
}

template <class T>
void convert_to_vec(std::vector<std::string>& args_vec, const T& val) {
	std::stringstream ss;
	std::string conv_val;
	ss << val;
	ss >> conv_val;
	args_vec.push_back(conv_val);
}

template <class T, class ...Args>
void convert_to_vec(std::vector<std::string>& args_vec, const T& val, const Args& ...args) {
	std::stringstream ss;
	std::string conv_val;
	ss << val;
	ss >> conv_val;
	args_vec.push_back(conv_val);
	convert_to_vec(args_vec, args...);
}

int char2int(char x) {
	return x - '0';
}

template <class ...Args>
std::string format(const std::string& str, const Args& ...args) { // format("string {0}", "input0")
	std::vector<std::string> args_vec;
	convert_to_vec(args_vec, args...);
	int num_args = args_vec.size();
	int len = str.size();
	bool in_brackets = false;
	int subst = -1;
	std::string res = "";
	for (int i = 0; i < len; i++) {
		if (in_brackets) {
			if (str[i] == '}') {
				if (subst >= num_args) {
					throw Error("Number in brackets is too large", __FILE__, __LINE__);
				}
				if (subst == -1) {
					throw Error("No number in brackets", __FILE__, __LINE__);
				}
				res += args_vec[subst];
				subst = -1;
				in_brackets = false;
			}
			else if (i == len - 1) {
				throw Error("End of string before closing brackets", __FILE__, __LINE__);
			}
			else if (std::isdigit(str[i])) {
				if (subst == -1) {
					subst = char2int(str[i]);
				}
				else {
					subst = subst * 10 + char2int(str[i]);
				}
			}
			else {
				throw Error("Not a number met inside brackets", __FILE__, __LINE__);
			}
		}
		else if (str[i] == '{') {
			in_brackets = true;
		}
		else if (str[i] == '}') {
			throw Error("Closing bracket before opening one", __FILE__, __LINE__);
		}
		else {
			res += str[i];
		}
	}
	return res;
}

#endif //FORMATTER_H