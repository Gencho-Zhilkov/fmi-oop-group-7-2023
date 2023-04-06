#ifndef FMI_OOP_CAR_VECTOR_HPP
#define FMI_OOP_CAR_VECTOR_HPP

#include <cassert>
#include <cstddef>

#include "car.hpp"


class CarVector {
private:
	size_t count;
	size_t capacity;
	Car *data;

	void allocate(const size_t capacity) {
		// N.B! `data` is not freed by this method!
		// Callers should ensure no mem. leaks occur!
		this->count = 0;
		this->capacity = capacity;
		this->data = new Car[capacity];
	}

	void copy(const Car *arr, const size_t n) {
		assert(n <= capacity);
		for(size_t i = 0; i < n; i++) {
			data[i] = arr[i];
		}
		count = n;
	}

	void moveVector(CarVector&& that) {
		count = that.count;
		capacity = that.capacity;
		data = that.data;

		that.count = that.capacity = 0;
		that.data = nullptr;
	}

	void cleanup() {
		delete[] data;
	}

	void checkAndIncreaseCapacity() {
		assert (count <= capacity);
		if (count == capacity) {
			Car *oldArray = data;
			allocate(2 * capacity);
			copy(oldArray, count);
			delete[] oldArray;
		}
	}

public:
	CarVector() {
		allocate(10);
	}

	CarVector(const CarVector& that) {
		allocate(that.capacity);
		copy(that.data, that.count);
	}

	CarVector& operator =(const CarVector& that) {
		if (this != &that) {
			cleanup();
			allocate(that.capacity);
			copy(that.data, that.count);
		}
		return *this;
	}

	CarVector(CarVector&& that) {
		moveVector(std::move(that));
	}

	CarVector& operator =(CarVector&& that) {
		if (this != &that) {
			cleanup();
			moveVector(std::move(that));
		}
		return *this;
	}

	~CarVector() {
		cleanup();
	}

	Car& operator [](const size_t index) {
		if (index >= count) {
			throw std::out_of_range("Index out of range!");
		}
		return data[index];
	}

	const Car& operator [](const size_t index) const {
		if (index >= count) {
			throw std::out_of_range("Index out of range!");
		}
		return data[index];
	}

	void push_back(const Car& car) {
		checkAndIncreaseCapacity();

		data[count] = car;
		count++;
	}

	size_t size() const {
		return count;
	}
};

#endif /* FMI_OOP_CAR_VECTOR_HPP */
