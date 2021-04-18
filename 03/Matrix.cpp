#include "Matrix.h"

Matrix::Row::Row() {
	size = 0;
	data_ = nullptr;
}

Matrix::Row::Row(size_t columns) {
	size = columns;
	data_ = new int32_t[columns]();
}

Matrix::Row::~Row() {
	data_ = nullptr;
}

int32_t& Matrix::Row::operator[](size_t j) const {
	if (j >= size) {
		throw std::out_of_range("");
	}
	return data_[j];
}

Matrix::Row& Matrix::Row::operator*=(int32_t a) {
	for (size_t j=0; j < size; j++) {
		data_[j] *= a;
	}
	return *this;
}

Matrix::Row Matrix::Row::operator+(const Matrix::Row b) const{
	if (size != b.size) {
		throw std::length_error("");
	}
	Matrix::Row res(size);
	for (size_t j=0; j < size; j++) {
		res.data_[j] = data_[j] + b.data_[j];
	}
	return res;
}

bool Matrix::Row::operator==(const Matrix::Row b) const {
	if (size != b.size) {
		return false;
	}
	for (size_t j=0; j < size; j++) {
		if (data_[j] != b.data_[j]) {
			return false;
		}
	}
	return true;
}

bool Matrix::Row::operator!=(const Matrix::Row b) const {
	return !(*this == b);
}

Matrix::Matrix(size_t rows, size_t columns) {
	i_rows = rows;
	j_columns = columns;
	rows_ = new Row[i_rows];
	for (size_t i=0; i < i_rows; i++) {
		rows_[i] = Row(j_columns);
	}
}

Matrix::~Matrix() {
	rows_ = nullptr;
}

Matrix::Row& Matrix::operator[](size_t i) const {
	if (i >= i_rows) {
		throw std::out_of_range("");
	}
	return rows_[i];
}

Matrix& Matrix::operator*=(int32_t a) {
	for (size_t i=0; i < i_rows; i++) {
		rows_[i] *= a;
	}
	return *this;
}

Matrix Matrix::operator+(Matrix const &b) const {
	if ((i_rows != b.i_rows) && (j_columns != b.j_columns)) {
		throw std::length_error("");
	}
	Matrix res(i_rows, j_columns);
	for (size_t i=0; i < i_rows; i++) {
		res.rows_[i] = rows_[i] + b.rows_[i];
	}
	return res;
}

bool Matrix::operator==(const Matrix b) const {
	if ((i_rows != b.i_rows) && (j_columns != b.j_columns)) {
		return false;
	}
	for (size_t i=0; i < i_rows; i++) {
		if (rows_[i]!= b.rows_[i]) {
			return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix b) const {
	return !(*this == b);
}

std::ostream& operator<<(std::ostream &out, const Matrix &matrix) {
	for (size_t i=0; i < matrix.i_rows; i++) {
		for (size_t j=0; j < matrix.j_columns; j++) {
			out << matrix[i][j] << " ";
		}
		out << '\n';
	}
	return out;
}

size_t Matrix::getRows() const {
	return i_rows;
}

size_t Matrix::getColumns() const {
	return j_columns;
}