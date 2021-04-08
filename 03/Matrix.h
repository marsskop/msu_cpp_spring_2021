#include <iostream>
#include <cstdint>
#include <cassert>
#include <string>
#include <sstream>

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
	struct Row {
		int32_t* data_ = nullptr;
		size_t size = 0;
		Row();
		explicit Row(size_t columns);
		int32_t& operator[](size_t j) const;
		Row& operator*=(int32_t a);
		Row operator+(Row b);
		bool operator==(Row b);
		bool operator!=(Row b);
	};
	Row* rows_ = nullptr;
	size_t i_rows = 0;
	size_t j_columns = 0;
public:
	explicit Matrix(size_t rows, size_t columns);
	~Matrix();
	Row& operator[](size_t i) const;
	Matrix& operator*=(int32_t a);
	Matrix operator+(Matrix const &b);
	bool operator==(Matrix b);
	bool operator!=(Matrix b);
	size_t getRows();
	size_t getColumns();
	friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);
};

#endif //MATRIX_H