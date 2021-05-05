#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <cassert>
#include <cstddef>
#include <algorithm>
#include <random>

const size_t SIZE_MAXV = 4294967295;

template <class T>
class Allocator {
public: // allocator_traits?
	T* allocate(size_t n) {
		auto p = static_cast<T*>(malloc(n * sizeof(T)));
		if (p == nullptr) {
			throw std::bad_alloc();
		}
		return p;
	}
	void deallocate(T* p, size_t n) {
		free(p);
	}

	void construct(T* p, const T& val) { // maybe use std::allocator_traits?
		new(p) T(val);
	}

	void destroy(T* ptr) {
		ptr->~T();
	}
};

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
public:
	Iterator<T>(T* ptr): data(ptr) {}
	Iterator<T>(const Iterator<T>& it): data(it.data) {}

	T& operator*() const {
		return *data;
	}
	T* operator->() {
		return data;
	}

	Iterator& operator--() {
		--data;
		return *this;
	}
	Iterator& operator++() {
		++data;
		return *this;
	}
	Iterator& operator-=(size_t num) {
		data -= num;
		return *this;
	}
	Iterator& operator+=(size_t num) {
		data += num;
		return *this;
	}
	Iterator operator--(int) {
		Iterator<T> tmp = *this;
		--(*this);
		return tmp;
	}
	Iterator operator++(int) {
		Iterator<T> tmp = *this;
		++(*this);
		return tmp;
	}
	Iterator operator-(size_t num) {
		return Iterator<T>(data - num);
	}
	Iterator operator+(size_t num) {
		return Iterator<T>(data + num);
	}

	std::ptrdiff_t operator-(const Iterator<T> it) {
		return data - it.data;
	}

	bool operator==(const Iterator<T>& it) {
		return data == it.data;
	}
	bool operator!=(const Iterator<T>& it) {
		return !(*this == it);
	}
private:
	T* data;
};

template <class T, class alloc_t=Allocator<T>>
class Vector {
private:
	size_t size_;
	size_t cap;
	alloc_t alloc;
	T* data;
	using Iterator = Iterator<T>;
public:
	Vector(size_t num) noexcept: size_(0), cap(num), data(alloc.allocate(num)) {}
	Vector(size_t num, const T& val) noexcept: size_(num), cap(num), data(alloc.allocate(num)) {
		for (size_t i=0; i != num; i++) {
			alloc.construct(data + i, val);
		}
	}
	Vector(const Vector& vec) noexcept: size_(vec.size()), cap(vec.size()), data(vec.data) {
		for (size_t i=0; i != size_; i++) {
			alloc.construct(data + i, vec[i]);
		}
	}
	~Vector() noexcept {
		for (size_t i=0; i != size_; i++) {
			alloc.destroy(data + i);
		}
	}

	// element access
	T& operator[](size_t ind) const {
		if (ind >= size_) {
			throw std::out_of_range("");
		}
		return data[ind];
	}

	// capacity
	size_t size() const {
		return size_;
	}
	bool empty() const {
		return (size_ == 0);
	}
	void reserve(size_t new_cap) {
		if (new_cap > cap) {
			T* old_data = data;
			size_t old_cap = cap;
			data = alloc.allocate(new_cap);
			cap = new_cap;
			for (size_t i=0; i != size_; i++) {
				alloc.construct(data + i, old_data[i]);
				alloc.destroy(old_data + i);
			}
			alloc.deallocate(old_data, old_cap);
		}
	}
	size_t capacity() const {
		return cap;
	}

	// modifiers
	void clear() {
		resize(0);
	}
	void push_back(const T& val) {
		resize(size_ + 1, val);
	}

	void push_back(const T* val) {
		resize(size_ + 1, *val);
	}

	template <typename... Args>
	void emplace_back(Args&&... args) {
		void* new_p = alloc.allocate(1);
		push_back(new (new_p) T(std::forward<Args>(args)...));
	}
	void pop_back() {
		if (size_ > 0) {
			resize(size_ - 1);
		}
	}
	void resize_smaller(size_t new_size) {
		T* new_p = alloc.allocate(new_size);
		for (size_t i=0; i != new_size; i++) {
			alloc.construct(new_p + i, data[i]);
		}
		for (size_t i=0; i != size_; i++) {
			alloc.destroy(data + i);
		}
		alloc.deallocate(data, size_);
		data = new_p;
		size_ = new_size;
	}
	void expand_capacity(size_t new_size) {
		size_t new_cap;
		if (cap == 0) {
			new_cap = 1;
		}
		else if (cap < SIZE_MAXV / 2) {
			new_cap = cap * 16 / 10;
		}
		else {
			new_cap = SIZE_MAXV;
		}
		if (new_size > new_cap) {
			new_cap = new_size;
		}
		reserve(new_cap);
	}
	void resize(size_t new_size) {
		if (size_ == new_size) {
			return;
		}
		if (size_ > new_size) {
			resize_smaller(new_size);
		}
		if (cap < new_size) {
			expand_capacity(new_size);
		}
		size_ = new_size;
	}
	void resize(size_t new_size, const T& val) {
		size_t old_size = size_;
		resize(new_size);
		if (new_size > old_size) {
			for (size_t i=old_size; i != new_size; i++) {
				alloc.construct(data + i, val);
			}
		}
	}

	// iterators
	Iterator begin() {
		return Iterator(data);
	}
	Iterator end() {
		return Iterator(data + size_);
	}
	std::reverse_iterator<Iterator> rbegin() {
		return std::reverse_iterator<Iterator>(end());
	}
	std::reverse_iterator<Iterator> rend() {
		return std::reverse_iterator<Iterator>(begin());
	}
};

#endif //VECTOR_H