#include "BigInt.h"

void ConstructorTest() {
	BigInt a;
	BigInt b(-12345);
	BigInt c("123456789012345678901234567890");

	char* aa = a.getNum();
	assert(aa == nullptr);

	char* bb = b.getNum();
	const char* bbns = "-12345";
	for (int i = 0; i < strlen(bb); i++) {
		assert(bb[i] = bbns[i]);
	}

	char* cc = c.getNum();
	const char* ccns = "123456789012345678901234567890";
	for (int i = 0; i < strlen(cc); i++) {
		assert(cc[i] = ccns[i]);
	}
}

void SumTest() {
	BigInt a("1000");
	BigInt b("999");
	BigInt c("-1000");
	BigInt d("-999");
	int e = 1000;
	char* xx;
	const char* xxns;

	BigInt x = a + b;
	xx = x.getNum();
	xxns = "1999";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = c + b;
	xx = x.getNum();
	xxns = "-1";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = a + d;
	xx = x.getNum();
	xxns = "1";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = c + d;
	xx = x.getNum();
	xxns = "-1999";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = a + e;
	xx = x.getNum();
	xxns = "2000";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}
}

void SubtractTest() {
	BigInt a("1000");
	BigInt b("999");
	BigInt c("-1000");
	BigInt d("-999");
	int e = 1000;
	char* xx;
	const char* xxns;

	BigInt x = a - b;
	xx = x.getNum();
	xxns = "1";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = c - b;
	xx = x.getNum();
	xxns = "-1999";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = a - d;
	xx = x.getNum();
	xxns = "1999";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = c - d;
	xx = x.getNum();
	xxns = "-1";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = d - c;
	xx = x.getNum();
	xxns = "1";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = a - e;
	xx = x.getNum();
	xxns = "0";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}
}

void MultiplyTest() {
	BigInt a("12");
	BigInt b("1234");
	BigInt c("-12");
	BigInt d("-1234");
	BigInt e("0");
	int f = 12;
	char* xx;
	const char* xxns;

	BigInt x = a * b;
	xx = x.getNum();
	xxns = "14808";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = c * b;
	xx = x.getNum();
	xxns = "-14808";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = c * d;
	xx = x.getNum();
	xxns = "14808";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = a * e;
	xx = x.getNum();
	xxns = "0";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	x = a * f;
	xx = x.getNum();
	xxns = "14808";
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}
}

void CompareTest() {
	BigInt a("1000");
	BigInt b("999");
	BigInt c("-1000");
	BigInt d("-999");
	BigInt e("1000");
	assert(a == e);
	assert(a > b);
	assert(a != c);
	assert(a > c);
	assert(c < d);
	assert(d >= c);
}

void CopyTest() {
	BigInt a("1234");
	BigInt b(a);
	assert(a == b);

	BigInt c("1234");
	BigInt d("4321");
	d = c;
	assert(d == c);
}

void MoveTest() {
	const char* xxns = "1234";
	char* xx;

	BigInt a("1234");
	BigInt b(std::move(a));
	assert(!a.getNum());
	xx = b.getNum();
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}

	BigInt c("1234");
	BigInt d("4321");
	d = std::move(c);
	assert(!c.getNum());
	xx = d.getNum();
	for (int i = 0; i < strlen(xx); i++) {
		assert(xx[i] = xxns[i]);
	}
}

void OutTest() {
	BigInt a(-1234567890);
	std::ostringstream oss;
	std::string ans = "-1234567890";
	oss << a;
	assert(oss && (oss.str() == ans));
}

int main() {
	ConstructorTest();
	SumTest();
	SubtractTest();
	CompareTest();
	MultiplyTest();
	CopyTest();
	MoveTest();
	OutTest();
	std::cout << "Success!" << std::endl;
	return 0;
}