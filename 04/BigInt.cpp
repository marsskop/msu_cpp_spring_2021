#include "BigInt.h"

BigInt::BigInt() {
	num = nullptr;
	minus = false;
}

BigInt::BigInt(int number) {
	minus = number <= 0;
	char* buff = new char[11];
	sprintf(buff, "%d", number > 0 ? number : -number);
	num = buff;
	num[strlen(num)] = '\0';
}

BigInt::BigInt(const char* number) {
	minus = number[0] == '-';
	int offset = minus ? 1 : 0;
	num = new char[strlen(number) + offset];
	std::copy(number + offset, number + strlen(number) + offset, num);
	num[strlen(number)] = '\0';
}

BigInt::~BigInt() {
	delete[] num;
}

BigInt::BigInt(const BigInt &a) {
	if (this == &a) {
		return;
	}
	num = new char[strlen(a.num)];
	std::copy(a.num, a.num + strlen(a.num), num);
	num[strlen(a.num)] = '\0';
	minus = a.minus;
}

BigInt::BigInt(BigInt &&a) {
	if (this == &a) {
		return;
	}
	num = new char[strlen(a.num)];
	std::copy(a.num, a.num + strlen(a.num), num);
	num[strlen(a.num)] = '\0';
	minus = a.minus;
	a.minus = false;
	a.num = nullptr;
}

BigInt& BigInt::operator=(const BigInt &a) {
	if (this == &a) {
		return *this;
	}
	minus = a.minus;
	delete[] num;
	char* tmp = new char[strlen(a.num) + 1];
	num = tmp;
	std::copy(a.num, a.num + strlen(a.num), num);
	num[strlen(a.num)] = '\0';
	return *this;
}

BigInt& BigInt::operator=(BigInt &&a) {
	if (this == &a) {
		return *this;
	}
	delete[] num;
	char* tmp = new char[strlen(a.num) + 1];
	num = tmp;
	std::copy(a.num, a.num + strlen(a.num), num);
	num[strlen(a.num)] = '\0';
	minus = a.minus;
	a.minus = false;
	a.num = nullptr;
	return *this;
}

char BigInt::digit2char(int x) {
	return x + '0';
}

int BigInt::char2digit(char x) {
	return x - '0';
}

bool BigInt::asmaller(const char* a, const char* b) {
	// compare two string of digits
	int sizea = strlen(a);
	int sizeb = strlen(b);
	if (sizea < sizeb) {
		return true;
	}
	else if (sizea > sizeb) {
		return false;
	}
	else {
		for (int i = 0; i < sizea; i++){
			if (a[i] < b[i]) {
				return true;
			}
			else if (a[i] > b[i]) {
				return false;
			}
		}
	}
	return false;
}

BigInt BigInt::sum(const BigInt& a, const BigInt& b) {
	// sum of two positive char ints
	char* astr = a.num;
	char* bstr = b.num;
	int sizea = strlen(astr);
	int sizeb = strlen(bstr);
	int sizemax = sizea > sizeb ? sizea : sizeb;
	char* res = new char[sizemax + 1];
	int carry = 0;
	int i = 0;

	for (i = 0; i < sizemax; i++) {
		int digita, digitb;
		if (i < sizea) {
			digita = char2digit(astr[sizea - i - 1]);
		}
		else {
			digita = 0;
		}
		if (i < sizeb) {
			digitb = char2digit(bstr[sizeb - i -1]);
		}
		else {
			digitb = 0;
		}

		int sum = digita + digitb + carry;
		carry = 0;
		if (sum > 9) {
			carry = 1;
			sum -= 10;
		}
		res[i] = digit2char(sum);
	}
	if (carry) {
		res[i] = digit2char(1);
		i++;
	}
	res[i] = '\0';

	for (i = 0; i < strlen(res) / 2; i++) {
		char tmp = res[i];
		res[i] = res[strlen(res) - i - 1];
		res[strlen(res) - i - 1] = tmp;
	}
	BigInt ans(res);
	ans.minus = false;
	return ans;
}

BigInt BigInt::subtract(const BigInt& a, const BigInt& b) {
	// subtraction of two BigInts, minus is ignored
	char* astr = a.num;
	char* bstr = b.num;
	bool ans_minus = false;
	if (asmaller(astr, bstr)) {
		char* tmp = astr;
		astr = bstr;
		bstr = tmp;
		ans_minus = true;
	}
	int sizea = strlen(astr);
	int sizeb = strlen(bstr);
	char* res = new char[sizea + 1];
	int carry = 0;
	int i = 0;

	for (i = sizeb - 1; i >= 0; --i) {
		int digita, digitb;
		digita = char2digit(astr[i + (sizea - sizeb)]);
		digitb = char2digit(bstr[i]);
		int sub = digita - digitb - carry;
		carry = 0;
		if (sub < 0) {
			carry = 1;
			sub += 10;
		}
		res[i + (sizea - sizeb)] = digit2char(sub);
	}
	for (i = sizea - sizeb - 1; i >= 0; --i) {
		int digita;
		digita = char2digit(astr[i]);
		int sub = digita - carry;
		carry = 0;
		if (sub < 0) {
			carry = 1;
			sub += 10;
		}
		res[i] = digit2char(sub);
	}
	int ind = sizea - 1;
	for (i = 0; i < sizea; i++) {
		if ((res[i] != '0') && (ind == sizea - 1)) {
			ind = i;
			break;
		}
	}
	for (i = 0; i < sizea - ind; i++) {
		res[i] = res[ind + i];
	}
	res[i] = '\0';
	BigInt ans(res);
	ans.minus = ans_minus;
	return ans;
}

BigInt BigInt::operator+(const BigInt &a) {
	if (!minus && !a.minus) {
		return sum(*this, a);
	}
	else if (minus && a.minus) {
		return -sum(*this, a);
	}
	else if (!minus && a.minus) {
		return subtract(*this, a);
	}
	else {
		return subtract(a, *this);
	}

}

BigInt BigInt::operator+(const int a) {
	BigInt tmp(a);
	return *this + tmp;
}

BigInt BigInt::operator-() {
	BigInt tmp(num);
	tmp.minus = !minus;
	return tmp;
}

BigInt BigInt::operator-(const BigInt &a) {
	if (!minus && !a.minus) {
		return subtract(*this, a);
	}
	else if (minus && a.minus) {
		return subtract(a, *this);
	}
	else if (!minus && a.minus) {
		return sum(*this, a);
	}
	else {
		return -sum(*this, a);
	}
}

BigInt BigInt::operator-(const int a) {
	BigInt tmp(a);
	return *this - tmp;
}

BigInt BigInt::naivemul(const BigInt& a, const BigInt& b) {
	char* astr = a.num;
	char* bstr = b.num;
	int sizea = strlen(astr);
	int sizeb = strlen(bstr);
	int i;
	char* res = new char[sizea + sizeb + 1];
	for (i = 0; i < sizea + sizeb; i++) {
		res[i] = '0';
	}
	res[i] = '\0';
	int carry = 0;
	for (i = sizea - 1; i >=0; i--) {
		int digita = char2digit(astr[i]);
		for (int j = sizeb-1; j >= 0; --j) {
			int digitb = char2digit(bstr[j]);
			int sum = digita * digitb + char2digit(res[i + j + 1]) + carry;
			res[i + j + 1] = digit2char(sum % 10);
			res[i + j] = digit2char(sum / 10 + char2digit(res[i + j]));
		}
	}
	int ind = sizea + sizeb - 1;
	for (i = 0; i < sizea + sizeb; i++) {
		if ((res[i] != '0') && (ind == sizea + sizeb - 1)) {
			ind = i;
			break;
		}
	}
	for (i = 0; i < sizea + sizeb - ind; i++) {
		res[i] = res[ind + i];
	}
	res[i] = '\0';
	BigInt ans(res);
	return ans;
}

BigInt BigInt::operator*(const BigInt &a) {
	if ((!minus && !a.minus) || (minus && a.minus)) {
		return naivemul(*this, a);
	}
	else {
		return -naivemul(*this, a);
	}
}

BigInt BigInt::operator*(const int a) {
	BigInt tmp(a);
	return *this * tmp;
}

bool BigInt::operator==(const BigInt &a) {
	if (this == &a) {
		return true;
	}
	if (minus != a.minus) {
		return false;
	}
	return (!asmaller(num, a.num) && !asmaller(a.num, num));

}

bool BigInt::operator!=(const BigInt &a) {
	return !(*this == a);
}

bool BigInt::operator>(const BigInt &a) {
	if (this == &a) {
		return false;
	}
	if (!minus && a.minus) {
		return true;
	}
	else if (minus && !a.minus) {
		return false;
	}
	else if (!minus && !a.minus) {
		return asmaller(a.num, num);
	}
	else {
		return asmaller(num, a.num);
	}
}

bool BigInt::operator>=(const BigInt &a) {
	return ((*this == a) || (*this > a));
}

bool BigInt::operator<(const BigInt &a) {
	return !(*this >= a);
}

bool BigInt::operator<=(const BigInt &a) {
	return !(*this > a);
}

char* BigInt::getNum() {
	if (not num) {
		return nullptr;
	}
	char* res = new char[strlen(num) + 2];
	int i = 0;
	if (minus) {
		res[i] = '-';
		i++;
		for (i; i < strlen(num) + 1; i++) {
			res[i] = num[i - 1];
		}
	}
	else {
		for (i; i < strlen(num); i++) {
			res[i] = num[i];
		}
	}
	res[i] = '\0';
	return res;
}

std::ostream& operator<< (std::ostream& oss, const BigInt& a) {
	if (not a.num) {
		oss << "";
		return oss;
	}
	if (a.minus) {
		oss << "-";
	}
	oss << a.num;
	return oss;
}