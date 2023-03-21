#include <stdexcept>
#include <cassert>
#include <iostream>


// A dummy object whose constructors and destructor print on stdout
class Dummy {
public:
	Dummy() {
		std::cout << "Dummy: default constructor, this=" << this << std::endl;
	}

	Dummy(const int v) {
		std::cout << "Dummy: constructor, this=" << this
				  << ", v=" << v << std::endl;
	}

	Dummy(const Dummy& that) {
		std::cout << "Dummy: copy constructor, this=" << this
				  << ", that=" << &that << std::endl;
	}

	Dummy(Dummy&& that) {
		std::cout << "Dummy: MOVE constructor, this=" << this
				  << ", that=" << &that << std::endl;
	}

	Dummy& operator =(const Dummy& that) {
		std::cout << "Dummy: assignment operator, this=" << this
				  << ", that=" << &that << std::endl;
		return *this;
	}

	Dummy& operator= (Dummy&& that) {
		std::cout << "Dummy: MOVE assignment operator, this=" << this
				  << ", that=" << &that << std::endl;
		return *this;
	}

	~Dummy() {
		std::cout << "Dummy: destructor, this=" << this << std::endl;
	}

	void doSomething() {
		std::cout << "Dummy: doSomething(), this=" << this << std::endl;
	}
};


class Dummy2 {
private:
	// Add two dummy members to see what's going on.
	Dummy d1;
	Dummy d2;

public:
	// Ensure that the compiler generates all the usual suspects.
	Dummy2() = default;
	Dummy2(const Dummy2&) = default;
	Dummy2(Dummy2&&) = default;
	Dummy2& operator =(const Dummy2&) = default;
	Dummy2& operator =(Dummy2&&) = default;
	~Dummy2() = default;

	// Add an additional custom constructors
	Dummy2(const int v1, const int v2): d1{v1}, d2{v2} {
	}
};

Dummy foo(const int v) {
	return Dummy{v};
}

int main() {
	// Insert your test code here, then compile and run ...
    Dummy2 dd{5, 7};
    return 0;
}
