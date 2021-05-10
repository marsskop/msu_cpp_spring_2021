#include "DeSerializer.h"

Error Serializer::write(bool arg) {
	if (arg) {
		out_ << "true" << Separator;
	}
	else {
		out_ << "false" << Separator;
	}
	return Error::NoError;
}

Error Serializer::write(uint64_t arg) {
	out_ << arg << Separator;
	return Error::NoError;
}

Error Deserializer::read(bool& arg) {
	std::string text;
	in_ >> text;
	if (text.size() == 0) {
		return Error::CorruptedArchive;
	}
	if (text == "true") {
		arg = true;
	}
	else if (text == "false") {
		arg = false;
	}
	else {
		return Error::CorruptedArchive;
	}
	return Error::NoError;
}

Error Deserializer::read(uint64_t& arg) {
	std::string text;
	in_ >> text;
	if (text.size() == 0) {
		return Error::CorruptedArchive;
	}
	if (strspn(text.c_str(), "0123456789") == text.size()) {
		try {
			arg = std::stoull(text);
		}
		catch (std::out_of_range) {
			return Error::CorruptedArchive;
		}
	}
	else {
		return Error::CorruptedArchive;
	}
	return Error::NoError;
}