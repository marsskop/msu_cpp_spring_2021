#ifndef EXTERNALSORT_H
#define EXTERNALSORT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <cassert>

const uint64_t MAX_CAP = 1048576; // 8388608 / 8


struct file_interface {
	std::ifstream read;
	std::ofstream write;
	std::string name;
	uint64_t size_ = 0;
};

/**
 * First, we count size of input. File is in binary format and consists of uint64_t numbers.
 *
 * ...
 *
 * @param[in] filename name of the binary file
 * @return size of input
 */
uint64_t InputSize(const std::string filename) {
	std::ifstream file(filename, std::ios_base::binary);
	std::streampos start, end;
	start = file.tellg();
	file.seekg(0, std::ios_base::end);
	end = file.tellg();
	return (end - start) / sizeof(uint64_t);
}

/**
 * Auxiliary function for MergeSort.
 *
 * ...
 *
 * @param[out] vec vector of uint64_t
 * @param[in] l left index
 * @param[in] m middle index for merge
 * @param[in] r right index
 */
void Merge(std::vector<uint64_t> vec, uint64_t l, uint64_t m, uint64_t r) {
	uint64_t i, j, k;
	uint64_t left_len = m - l + 1;
	uint64_t right_len = r - m;
	std::vector<uint64_t> L(left_len);
	std::vector<uint64_t> R(right_len);
	for (i=0; i < left_len; i++) {
		L[i] = vec[l + i];
	}
	for (j=0; j < right_len; j++) {
		R[j] = vec[m + j + 1];
	}
	i = 0;
	j = 0;
	k = l;
	while (i < left_len && j < right_len) {
		if (L[i] <= R[j]) {
			vec[k++] = L[i++];
		}
		else {
			vec[k++] = R[j++];
		}
	}
	while (i < left_len) {
		vec[k++] = L[i++];
	}
	while (j < right_len) {
		vec[k++] = R[j++];
	}
}

/**
 * Chunks are sorted via MergeSort.
 *
 * ...
 *
 * @param[out] vec vector of uint64_t
 * @param[in] l left index of part to sort
 * @param[in] r right index of part to sort
 */
void MergeSort(std::vector<uint64_t> vec, uint64_t l, uint64_t r) {
	if (l < r) {
		uint64_t m = (r + l) / 2;
		MergeSort(vec, l, m);
		MergeSort(vec, m + 1, r);
		Merge(vec, l, m, r);
	}
}

/**
 * Merge chunks together.
 *
 * ...
 *
 * @pram[in] left left vector of chunks
 * @param[in] right right vector of chunks
 * @param[in] mk mark for thread support
 * @return merged sorted chunks
 */
file_interface& MergeFiles(file_interface& left, file_interface& right, uint64_t mk) {
	uint64_t left_len = left.size_;
	uint64_t right_len = right.size_;
	uint64_t sum_len = left_len + right_len;
	uint64_t left_num, right_num;
	std::string tmpname = "tmp" + std::to_string(mk) + ".txt";
	std::ofstream write_tmp(tmpname, std::ios_base::binary);
	left.read.open(left.name, std::ios_base::binary);
	right.read.open(right.name, std::ios_base::binary);

	left.read.read(reinterpret_cast<char*>(&left_num), sizeof(uint64_t));
	right.read.read(reinterpret_cast<char*>(&right_num), sizeof (uint64_t));
	while (left_len && right_len) {
		if (left_num <= right_num) {
			write_tmp.write(reinterpret_cast<char*>(left_num), sizeof(uint64_t));
			left.read.read(reinterpret_cast<char*>(&left_num), sizeof(uint64_t));
			left_len--;
		}
		else {
			write_tmp.write(reinterpret_cast<char*>(right_num), sizeof(uint64_t));
			right.read.read(reinterpret_cast<char*>(&right_num), sizeof(uint64_t));
			right_len--;
		}
	}
	while (left_len) {
		write_tmp.write(reinterpret_cast<char*>(left_num), sizeof(uint64_t));
		left.read.read(reinterpret_cast<char*>(&left_num), sizeof(uint64_t));
		left_len--;
	}
	while (right_len) {
		write_tmp.write(reinterpret_cast<char*>(right_num), sizeof(uint64_t));
		right.read.read(reinterpret_cast<char*>(&right_num), sizeof(uint64_t));
		right_len--;
	}
	left.read.close();
	right.read.close();
	write_tmp.close();

	std::ifstream read_tmp(tmpname, std::ios_base::binary);
	left.write.open(left.name, std::ios_base::binary);
	while (sum_len) {
		read_tmp.read(reinterpret_cast<char*>(&left_num), sizeof(uint64_t));
		left.write.write(reinterpret_cast<char*>(left_num), sizeof(uint64_t));
		sum_len--;
	}
	read_tmp.close();
	left.write.close();
	left.size_ += right.size_;
	std::remove(tmpname.c_str());
	return left;
}

/**
 * Sort chunks.
 *
 * ...
 *
 * @param[in] vec_files vector of sorted chunks
 * @param[in] l left index
 * @param[in] r right index
 * @param[in] mk mark for thread support
 * @return merged sorted chunks
 */
file_interface& SortFiles(std::vector<file_interface> vec_files, uint64_t l, uint64_t r, uint64_t mk) {
	if (l < r) {
		uint64_t m = (l + r) / 2;
		file_interface& left = SortFiles(vec_files, l, m, mk);
		file_interface& right = SortFiles(vec_files, m + 1, r, mk);
		return MergeFiles(left, right, mk);
	}
	return vec_files[l];
}

/**
 * Create a vector of sorted chunks.
 *
 * ...
 *
 * @param[in] num_files amount of chunks
 * @param[in] filename name of the binary file
 * @return vector of sorted chunks
 */
std::vector<file_interface> CreateFiles(const uint64_t num_files, const std::string filename) {
	std::ifstream file(filename, std::ios_base::binary);
	std::vector<uint64_t> data(MAX_CAP);
	std::vector<file_interface> vec_files(num_files);
	for (size_t i=0; i < num_files; i++) {
		while (!file.eof() && vec_files[i].size_ < MAX_CAP) {
			file.read(reinterpret_cast<char*>(&data[vec_files[i].size_]), sizeof(uint64_t));
			vec_files[i].size_++;
		}
		vec_files[i].name = "chunk" + std::to_string(i) + ".txt";
		MergeSort(data, 0, vec_files[i].size_ - 1);
		vec_files[i].write.open(vec_files[i].name, std::ios_base::binary);
		for (size_t j=0; j < vec_files[i].size_; j++){
			vec_files[i].write.write(reinterpret_cast<char*>(&data[j]), sizeof(uint64_t));
		}
		vec_files[i].write.close();
	}
	return vec_files;
}

/**
 * Main sorting function with double thread support.
 *
 * ...
 *
 * @param[in] filename name of binary file to sort
 * @return sorted file
 */
std::string MergeSortThreaded(const std::string filename) {
	uint64_t size_input = InputSize(filename);
	uint64_t num_files = size_input / MAX_CAP;
	if (size_input % MAX_CAP) {
		num_files++;
	}
	std::vector <file_interface> chunks = CreateFiles(num_files, filename);
	if (num_files > 1) {
		uint64_t div = file_num / 2 - 1;
		std::thread first(SortFiles, std::ref(chunks), 0, div, 1);
		std::thread second(SortFiles, std::ref(chunks), div + 1, num_files - 1, 2);
		first.join();
		second.join();
		MergeFiles(chunks[0], chunks[num_files - 1], 0);
		for (size_t i = 1; i != num_files; i++) {
			std::remove(chunks[i].name.c_str());
		}
	}
	std::string out_file = "sorted" + filename;
	std::ofstream fout(out_file, std::ios::binary | std::ios::out);
	std::ifstream fin0(chunks[0].name, std::ios::binary | std::ios::in);
	uint64_t n;
	while (!fin0.eof()) {
		fin0.read(reinterpret_cast<char *>(&n), sizeof(uint64_t));
		fout.write(reinterpret_cast<char *>(&n), sizeof(uint64_t));
	}
	fout.close();
	std::remove(chunks[0].name.c_str());
	return out_file;
}

#endif //EXTERNALSORT_H