#include "TokenParser.h"

void TokenParser::Parse(const std::string& text) {
	if (startcallback) {
		startcallback();
	}
	size_t pos = 0;
	size_t step;

	while (pos < text.length()) {
		step = 0;
		while (std::isspace(text[pos]) && (pos < text.length())) {
			pos++;
		}
		while (std::isdigit(text[pos + step]) && (pos + step < text.length())) {
			step++;
		}
		if ((!std::isdigit(text[pos + step])) && (!std::isspace(text[pos + step])) && (pos + step < text.length())) {
			while ((!std::isspace(text[pos + step])) && (pos + step < text.length())) {
				step++;
			}
			if (stringcallback) {
				stringcallback(text.substr(pos, step));
			}
		}
		else if ((pos + step <= text.length()) && (step > 0)) {
			try {
				std::uint64_t num = std::stoull(text.substr(pos, step));
				if (digitcallback) {
					digitcallback(num);
				}
			}
			catch (const std::out_of_range& e) {
				if (stringcallback) {
					stringcallback(text.substr(pos, step));
				}
			}
		}
		pos += step;
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