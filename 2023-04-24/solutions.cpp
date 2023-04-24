#include <iostream>
#include <stdexcept>


// Задача 1.
template <typename T>
void swap(T& a, T& b) {
	const T temp = a;
	a = b;
	b = temp;
}


// Задача 2.
template <typename T>
T* findMin(T* const array, const size_t size) {
	if (size == 0) {
		return nullptr;
	}

	T* min = &array[0]; // array
	for(size_t i = 1; i < size; i++) {
		if (array[i] < *min) {
			min = &array[i]; // (array + i)
		}
	}

	return min;
}


// Задача 3.
template <typename T>
struct SNode {
	SNode<T> *next;
	T data;

	SNode(const T& data, SNode<T> *next=nullptr): next(next), data(data) {}
};

template <typename T>
class SList {
private:
	SNode<T> *head_;

	SNode<T>* copy(const SNode<T>* const node) const {
		if(node == nullptr) {
			return nullptr;
		} else {
			SNode<T> *nodeCopy = copy(node->next);
			return new SNode{node->data, nodeCopy};
		}
	}

	void cleanup() {
		while (!isEmpty()) {
			removeFront();
		}
	}

	template <typename U>
	friend std::ostream& operator <<(std::ostream& out, const SList<U>& l);

public:
	SList(): head_(nullptr) {}

	SList(const SList<T>& that): head_(copy(that.head_)) {}

	SList& operator=(const SList<T>& that) {
		if (this != &that) {
			cleanup();
			head_ = copy(that.head_);
		}
		return *this;
	}

	SList(SList<T>&& that): head_(that.head_) {
		that.head_ = nullptr;
	}

	SList& operator=(SList<T>&& that) {
		if (this != &that) {
			swap(head_, that.head_);
		}
		return *this;
	}

	~SList() {
		cleanup();
	}

	void insertFront(const T& value) {
		SNode<T>* newNode = new SNode{value, head_};
		head_ = newNode;
	}

	void removeFront() {
		if (isEmpty()) {
			throw std::runtime_error("Trying to remove from empty list!");
		}

		SNode<T>* temp = head_;
		head_ = head_->next;

		delete temp;
	}

	bool isEmpty() const {
		return head_ == nullptr;
	}

	T& head() {
		if (isEmpty()) {
			throw std::out_of_range("Head of empty list!");
		}

		return head_->data;
	}

	const T& head() const {
		if (isEmpty()) {
			throw std::out_of_range("Head of empty list!");
		}

		return head_->data;
	}

	SList<T> tail() const {
		SList<T> res;
		if (!isEmpty()) {
			res.head_ = copy(head_->next);
		}
		return res;
	}
};

template <typename T>
std::ostream& operator <<(std::ostream& out, const SList<T>& l) {
	for (SNode<T> *node = l.head_; node != nullptr; node = node->next) {
		out << node->data << ' ';
	}

	return out;
}


// Примерни извиквания
int main() {
	// Зад. 1
	int a = 5, b = 7;
	std::cout << "Exercise 1: swap" << std::endl;
	std::cout << "Before: " << a << ' ' << b << std::endl;
	swap(a, b);
	std::cout << "After:" << a << ' ' << b << std::endl;
	std::cout << std::endl;

	// Зад. 2
	std::cout << "Exercise 2: findMin" << std::endl;
	long array[6] = {3, 2, 7, 1, 4, 5};
	for (size_t i = 0; i < 6; i++) {
		std::cout << i << ": " << array[i] << std::endl;
	}
	const long *min = findMin(array, 6);
	std::cout << "min = " << *min << " at index " << (min - array) << std::endl;
	std::cout << std::endl;

	// Зад. 3
	std::cout << "Exercise 3: SList" << std::endl;
	SList<int> list;
	std::cout << "Empty list: " << list << std::endl;

	list.insertFront(1);
	list.insertFront(2);
	list.insertFront(3);
	std::cout << "Insert Front 1, 2, 3 => "<< list << std::endl;

	list.removeFront();
	std::cout << "Remove Front => "<< list << std::endl;

	std::cout << "Get tail" << std::endl;
	SList<int> tail = list.tail();
	std::cout << "List: "<< list << std::endl;
	std::cout << "Tail: "<< tail << std::endl;

	std::cout << "Insert tail 4" << std::endl;
	tail.insertFront(4);
	std::cout << "List: "<< list << std::endl;
	std::cout << "Tail: "<< tail << std::endl;

	return 0;
}
