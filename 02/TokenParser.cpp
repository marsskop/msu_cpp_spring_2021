#include "TokenParser.h"

void TokenParser::Parse(const std::string& text) {
	if (startcallback) {
		startcallback();
	}
	size_t pos = 0;
	size_t step;

	while (pos < text.length()) {
		step = 0;
		while (std::isspace(text[pos])) {
			pos++;
		}
		while (std::isdigit(text[pos + step])) {
			step++;
		}
		if ((!std::isdigit(text[pos + step])) && (!std::isspace(text[pos + step]))) {
			while ((!std::isspace(text[pos + step])) && (pos + step < text.length())) {
				step++;
			}
			if (stringcallback) {
				stringcallback(text.substr(pos, step));
			}
			pos += step;
		}
		else {
			auto num = std::stoi(text.substr(pos, step));
			if (digitcallback) {
				digitcallback(num);
			}
			pos += step;
		}
	}

	if (endcallback) {
		endcallback();
	}
}

void TokenParser::SetStartCallback(startendcall callback) {
	startcallback = callback;
}

void TokenParser::SetEndCallback(startendcall callback) {
	endcallback = callback;
}

void TokenParser::SetDigitTokenCallback(digitcall callback) {
	digitcallback = callback;
}

void TokenParser::SetStringTokenCallback(stringcall callback) {
	stringcallback = callback;
}