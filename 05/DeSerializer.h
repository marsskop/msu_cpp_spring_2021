#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdint>
#include <cassert>

#ifndef DESERIALIZER_H
#define DESERIALIZER_H

enum class Error {
	NoError,
	CorruptedArchive
};

class Serializer {
private:
	static constexpr char Separator = ' ';
	std::ostream& out_;
	Error error;
public:
	explicit Serializer(std::ostream& out): out_(out) {}
	template <class T> Error save(T& object) {
		return object.serialize(*this);
	}
	template <class... ArgsT> Error operator()(ArgsT... args) {
		return process(args...);
	}
private:
	template <class T> Error process(T arg) {
		return write(arg);
	}
	template <class T, class... ArgsT> Error process(T arg, ArgsT... args) {
		error = process(arg);
		if (error == Error::NoError) {
			return process(args...);
		}
		else {
			return Error::CorruptedArchive;
		}
	}
	Error write(bool arg);
	Error write(uint64_t arg);
};

class Deserializer {
private:
	static constexpr char Separator = ' ';
	std::istream& in_;
	Error error;
public:
	explicit Deserializer(std::istream& in): in_(in) {}
	template <class T> Error load(T& object) {
		return object.serialize(*this);
	}
	template <class... ArgsT> Error operator()(ArgsT&... args) {
		return process(args...);
	}
private:
	template <class T> Error process(T& arg) {
		return read(arg);
	}
	template <class T, class... ArgsT> Error process(T& arg, ArgsT&... args) {
		error = process(arg);
		if (error == Error::NoError) {
			return process(args...);
		}
		else {
			return Error::CorruptedArchive;
		}
	}
	Error read(bool& arg);
	Error read(uint64_t& arg);
};

#endif //DESERIALIZER_H