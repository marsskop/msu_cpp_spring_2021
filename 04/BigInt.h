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

	char digit2char(int x);
	int char2digit(char x);
	bool asmaller(const char* a, const char* b);
	BigInt sum(const BigInt& a, const BigInt& b);
	BigInt subtract(const BigInt& a, const BigInt& b);
	BigInt naivemul(const BigInt& a, const BigInt& b);
public:
	BigInt();
	BigInt(int number);
	BigInt(const char* number);
	~BigInt();

	BigInt(const BigInt& a);
	BigInt(BigInt&& a);
	BigInt& operator=(const BigInt& a);
	BigInt& operator=(BigInt&& a);

	BigInt operator+(const BigInt& a);
	BigInt operator+(const int a);
	BigInt operator-();
	BigInt operator-(const BigInt& a);
	BigInt operator-(const int a);
	BigInt operator*(const BigInt& a);
	BigInt operator*(const int a);

	bool operator==(const BigInt& a);
	bool operator!=(const BigInt& a);
	bool operator>(const BigInt& a);
	bool operator>=(const BigInt& a);
	bool operator<(const BigInt& a);
	bool operator<=(const BigInt& a);

	char* getNum();

	friend std::ostream& operator<<(std::ostream& oss, const BigInt& a);
};

#endif //BIGINT_H