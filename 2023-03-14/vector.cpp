#include <iostream>
#include <stdexcept>
#include <cassert>

const size_t INITIAL_CAPACITY = 10;

class IntVector {
private:
	size_t count;
	size_t capacity;
	int* array;

	void cleanup() {
		delete[] array;
	}

	void copy(const IntVector& that) {
		count = that.count;
		capacity = that.capacity;
		array = new int[capacity];
		for(size_t i = 0; i < count; i++) {
			array[i] = that.array[i];
		}
	}

public:
	IntVector(): count{0}, capacity{INITIAL_CAPACITY} {
		array = new int[capacity];
	}

	IntVector(const IntVector& that) {
		copy(that);
	}

	IntVector& operator =(const IntVector& that) {
		if (this != &that) {
			cleanup();
			copy(that);
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

	int get(const size_t pos) const {
		if (pos >= count) {
			throw std::out_of_range("Trying to access element after the end!");
		}
		return array[pos];
	}

	void append(const int value) {
		assert (count <= capacity);
		if (count == capacity) {
			int *newArray = new int[2 * capacity];
			capacity *= 2;
			for (size_t i = 0; i < count; i++) {
				newArray[i] = array[i];
			}
			delete[] array;
			array = newArray;
		}

		array[count] = value;
		count++;
	}

	void pop() {
		if (isEmpty()) {
			throw std::out_of_range("Trying to remove element from empty vector!");
		}
		count--;
	}
};


void print(const IntVector& v) {
	for(size_t i = 0; i < v.size(); i ++) {
		std::cout << v.get(i) << ' ';
	}
	std::cout << std::endl;
}

int main() {
	IntVector v{};
	print(v);

	try {
		v.get(1);
		assert (false);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	for(int i = 1; i < 15; i ++) {
		v.append(i);
		print(v);
	}

	IntVector v2{};
	v = v2;

	return 0;
}
