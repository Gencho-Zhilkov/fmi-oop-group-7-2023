#include <iostream>
#include <stdexcept>
#include <cassert>


const size_t INITIAL_CAPACITY = 10;
const size_t VECTOR_VALUE_NOT_FOUND = -1ull;


class IntVector {
private:
	size_t count;
	size_t capacity;
	int* array;

	void allocate(const size_t capacity) {
		// N.B! `array` is not freed by this method!
		// Callers should ensure no mem. leaks occur!
		this->capacity = capacity;
		this->array = new int[capacity];
	}

	void cleanup() {
		delete[] array;
	}

	void copy(const int *arr, const size_t n) {
		assert(n <= capacity);
		for(size_t i = 0; i < n; i++) {
			array[i] = arr[i];
		}
		count = n;
	}

	void checkAndIncreaseCapacity() {
		assert (count <= capacity);
		if (count == capacity) {
			int *oldArray = array;
			allocate(2 * capacity);
			copy(oldArray, count);
			delete[] oldArray;
		}
	}

public:
	IntVector(): count{0} {
		allocate(INITIAL_CAPACITY);
	}

	IntVector(const IntVector& that) {
		allocate(that.capacity);
		copy(that.array, that.count);
	}

	IntVector(IntVector&& that):
		count{that.count}, capacity{that.capacity}, array{that.array} {
		// Set to `nullptr` otherwise it will be freed by `that`'s dtor!
		that.array = nullptr;
	}

	IntVector& operator =(const IntVector& that) {
		if (this != &that) {
			cleanup();
			allocate(that.capacity);
			copy(that.array, that.count);
		}
		return *this;
	}

	IntVector& operator =(IntVector&& that) {
		if (this != &that) {
			count = that.count;
			capacity = that.capacity;
			array = that.array;
			that.array = nullptr;
		}
		return *this;
	}

	~IntVector() {
		cleanup();
	}

	size_t size() const {
		return count;
	}

	bool isEmpty() const {
		return size() == 0;
	}

	// Add elements
	void append(const int value) {
		checkAndIncreaseCapacity();
		array[count] = value;
		count++;
	}

	void insert(const size_t pos, const int value) {
		if (pos >= count) {
			throw std::out_of_range("Trying to insert element after the end!");
		}
		checkAndIncreaseCapacity();

		for(size_t i = count; i > pos; i--) {
			array[i] = array[i - 1];
		}
		array[pos] = value;
		count++;
	}

	// Remove elements
	void pop() {
		if (isEmpty()) {
			throw std::out_of_range("Trying to remove element from empty vector!");
		}
		count--;
	}

	void remove(const size_t pos) {
		if (pos >= count) {
			throw std::out_of_range("Trying to remove element after the end!");
		}

		for (size_t i = pos + 1; i < count; i++) {
			array[i - 1] = array[i];
		}
		count--;
	}

	void clear() {
		count = 0;
	}

	// Element getter and setter
	int get(const size_t pos) const {
		if (pos >= count) {
			throw std::out_of_range("Trying to access element after the end!");
		}
		return array[pos];
	}

	void set(const size_t pos, const int value) {
		if (pos >= count) {
			throw std::out_of_range("Trying to access element after the end!");
		}
		array[pos] = value;
	}

	size_t find(const int value) const {
		for (size_t i = 0; i < count; i++) {
			if (array[i] == value) {
				return i;
			}
		}
		return VECTOR_VALUE_NOT_FOUND;
	}

};


void print(const char *name, const IntVector& v) {
	std::cout << name << ": ";
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << v.get(i) << ' ';
	}
	std::cout << std::endl;
}

int main() {
	// Create empty vector
	IntVector v1{};
	print("v1", v1);

	// Check that trying get an element from an empty vector raises an exception
	try {
		v1.get(0);
		assert (false);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	// Fill it up with values.
	for(int i = 0; i < 15; i ++) {
		v1.append(i);
		print("v1", v1);
	}

	// Call copy constructor
	IntVector v2{v1};
	print("v2", v2);

	// Remove element from
	v2.remove(10);
	print("v2", v2);
	v2.insert(10, -1);
	print("v2", v2);

	// Check that v1 has **not** been changed!
	print("v1", v1);

	// Call assignment operator
	IntVector v3{};
	v3 = v1;
	print("v3", v3);

	v3.pop();
	print("v3", v3);

	for (const int i: {1, 3, 5, 7, 17}) {
		std::cout << "v3.find(" << i << ") = " << v3.find(i) << std::endl;
	}

	return 0;
}
