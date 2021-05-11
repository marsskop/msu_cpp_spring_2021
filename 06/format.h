#ifndef FORMATTER_H
#define FORMATTER_H

#include <iostream>
#include <cstring>
#include <sstream>
#include <cassert>
#include <exception>
#include <vector>
#include <type_traits>

const int INT_MAX = 2147483647;

struct InvArgExcept : public std::invalid_argument {
	using std::invalid_argument::invalid_argument;
};

struct DomExcept : public std::domain_error {
	using std::domain_error::domain_error;
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
	int max_subst = -1;
	std::string res = "";
	for (int i = 0; i < len; i++) {
		if (in_brackets) {
			if (str[i] == '}') {
				if (subst >= num_args) {
					throw InvArgExcept("Number in brackets is too large");
				}
				if (subst == -1) {
					throw InvArgExcept("No number in brackets");
				}
				if (subst > max_subst) {
					max_subst = subst;
				}
				res += args_vec[subst];
				subst = -1;
				in_brackets = false;
			}
			else if (i == len - 1) {
				throw DomExcept("End of string before closing brackets");
			}
			else if (std::isdigit(str[i])) {
				if (subst == -1) {
					subst = char2int(str[i]);
				}
				else {
					if (subst >= (INT_MAX - char2int(str[i])) / 10) {
						throw InvArgExcept("Number in brackets is too large");
					}
					subst = subst * 10 + char2int(str[i]);
				}
			}
			else {
				throw InvArgExcept("Not a number met inside brackets");
			}
		}
		else if ((str[i] == '{') && (i == len - 1)) {
			throw DomExcept("End of string before closing brackets");
		}
		else if (str[i] == '{') {
			in_brackets = true;
		}
		else if (str[i] == '}') {
			throw DomExcept("Closing bracket before opening one");
		}
		else {
			res += str[i];
		}
	}
	if (max_subst < num_args - 1) {
		throw DomExcept("Excess of arguments");
	}
	return res;
}

#endif //FORMATTER_H