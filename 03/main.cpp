#include "Matrix.h"

void CreationTest() {
	const size_t rows = 3;
	const size_t cols = 5;
	Matrix m(rows, cols);
	assert(m.getRows() == rows);
	assert(m.getColumns() == cols);
}

void SingularTest() {
	Matrix m(1, 1);
	m[0][0] = 1;
	assert((m.getRows() == 1) && (m.getColumns() == 1));
	assert(m[0][0] == 1);
}

void IndexationTest() {
	const size_t rows = 3;
	const size_t cols = 5;
	bool exceptrows = false;
	bool exceptcols = false;
	Matrix m(rows, cols);
	for (size_t i=0; i < rows; i++) {
		for (size_t j=0; j < cols; j++) {
			m[i][j] = 1;
		}
	}
	for (size_t i=0; i < rows; i++) {
		for (size_t j=0; j < cols; j++) {
			assert(m[i][j] == 1);
		}
	}
	try {
		int32_t a = m[4][1];
	}
	catch (std::out_of_range) {
		exceptrows = true;
	}
	assert(exceptrows);
	try {
		int32_t a = m[1][6];
	}
	catch (std::out_of_range) {
		exceptcols = true;
	}
	assert(exceptcols);
}

void MultiplyTest() {
	const size_t rows = 3;
	const size_t cols = 5;
	Matrix m(rows, cols);
	for (size_t i=0; i < rows; i++) {
		for (size_t j=0; j < cols; j++) {
			m[i][j] = -1;
		}
	}
	m *= 3;
	for (size_t i=0; i < rows; i++) {
		for (size_t j=0; j < cols; j++) {
			assert(m[i][j] == -3);
		}
	}
}

void SumTest() {
	const size_t rows = 3;
	const size_t cols = 5;
	Matrix m1(rows, cols);
	Matrix m2(rows, cols);
	for (size_t i=0; i < rows; i++) {
		for (size_t j=0; j < cols; j++) {
			m1[i][j] = 1;
			m2[i][j] = 3;
		}
	}
	Matrix m3 = m1 + m2;
	for (size_t i=0; i < rows; i++) {
		for (size_t j=0; j < cols; j++) {
			assert(m1[i][j] == 1);
			assert(m2[i][j] == 3);
			assert(m3[i][j] == 4);
		}
	}
}

void SumLenTest() {
	bool except = false;
	const size_t rows = 3;
	const size_t cols = 5;
	Matrix m1(rows, cols);
	Matrix m2(cols, rows);
	try {
		Matrix m3 = m1 + m2;
	}
	catch (std::length_error) {
		except = true;
	}
	assert(except);
}

void EqualTest() {
	const size_t rows = 3;
	const size_t cols = 5;
	Matrix m1(rows, cols);
	Matrix m2(rows, cols);
	for (size_t i=0; i < rows; i++) {
		for (size_t j=0; j < cols; j++) {
			m1[i][j] = 1;
			m2[i][j] = 1;
		}
	}
	assert(m1 == m2);
}

void UnequalTest() {
	const size_t rows = 3;
	const size_t cols = 5;
	Matrix m1(rows, cols);
	Matrix m2(rows, cols);
	Matrix m3(cols, rows);
	for (size_t i=0; i < rows; i++) {
		for (size_t j=0; j < cols; j++) {
			m1[i][j] = 1;
			m2[i][j] = 2;
			m3[j][i] = 1;
		}
	}
	assert((m1 != m2) && (m1 != m3));
}

void OutputTest() {
	const size_t rows = 3;
	const size_t cols = 5;
	Matrix m(rows, cols);
	for (size_t i=0; i < rows; i++) {
		for (size_t j=0; j < cols; j++) {
			m[i][j] = 1;
		}
	}
	std::ostringstream oss;
	std::string ans = "1 1 1 1 1 \n1 1 1 1 1 \n1 1 1 1 1 \n";
	oss << m;
	assert(oss && (oss.str() == ans));
}

int main() {
	CreationTest();
	SingularTest();
	IndexationTest();
	MultiplyTest();
	SumTest();
	SumLenTest();
	EqualTest();
	UnequalTest();
	OutputTest();
	std::cout << "Success!" << std::endl;
	return 0;
}