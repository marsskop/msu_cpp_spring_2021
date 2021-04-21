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
		Row() {};
		explicit Row(size_t columns);
		~Row();
		int32_t& operator[](size_t j) const;
		Row& operator=(const Row& a);
		Row& operator*=(int32_t a);
		Row operator+(const Row &b) const;
		bool operator==(const Row &b) const;
		bool operator!=(const Row &b) const;
	};
	Row* rows_ = nullptr;
	size_t i_rows = 0;
	size_t j_columns = 0;
public:
	explicit Matrix(size_t rows, size_t columns);
	~Matrix();
	Row& operator[](size_t i) const;
	Matrix& operator*=(int32_t a);
	Matrix operator+(Matrix const &b) const;
	bool operator==(const Matrix &b) const;
	bool operator!=(const Matrix &b) const;
	size_t getRows() const;
	size_t getColumns() const;
	friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);
};

#endif //MATRIX_H
