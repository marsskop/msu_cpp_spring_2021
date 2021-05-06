#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cassert>
#include <sstream>

#ifndef BIGINT_H
#define BIGINT_H

class BigInt {
private:
	char *num;
	bool minus;

	char digit2char(int x) const;
	int char2digit(char x) const;
	bool asmaller(const char* a, const char* b) const;
	BigInt sum(const BigInt& a, const BigInt& b) const;
	BigInt subtract(const BigInt& a, const BigInt& b) const;
	BigInt naivemul(const BigInt& a, const BigInt& b) const;
public:
	BigInt();
	BigInt(int number);
	BigInt(const char* number);
	~BigInt();

	BigInt(const BigInt& a);
	BigInt(BigInt&& a);
	BigInt& operator=(const BigInt& a);
	BigInt& operator=(BigInt&& a);

	BigInt operator+(const BigInt& a) const;
	BigInt operator+(const int a) const;
	BigInt operator-() const;
	BigInt operator-(const BigInt& a) const;
	BigInt operator-(const int a) const;
	BigInt operator*(const BigInt& a) const;
	BigInt operator*(const int a) const;

	bool operator==(const BigInt& a) const;
	bool operator!=(const BigInt& a) const;
	bool operator>(const BigInt& a) const;
	bool operator>=(const BigInt& a) const;
	bool operator<(const BigInt& a) const;
	bool operator<=(const BigInt& a) const;

	char* getNum() const;

	friend std::ostream& operator<<(std::ostream& oss, const BigInt& a);
};

#endif //BIGINT_H