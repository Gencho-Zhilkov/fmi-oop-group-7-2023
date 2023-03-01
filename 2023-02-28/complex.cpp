#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cmath>


class Complex {

private:
	double real;
	double imag;

	// Write a number to a stream (for ex. `std::cout`)
	friend std::ostream& operator <<(std::ostream& os, const Complex& c);

public:
	// Constructor: can be called with 0, 1, or 2 arguments
	Complex(const double real=0, const double imag=0): real{real}, imag{imag} {}

	// Default copy ctor, assignment operator, and destructor
	Complex(const Complex&) = default;
	Complex& operator =(const Complex&) = default;
	~Complex() = default;

	Complex add(const Complex& c) const {
		return Complex{real + c.real, imag + c.imag};
	}

	Complex sub(const Complex& c) const {
		return Complex{real - c.real, imag - c.imag};
	}

	Complex mutiply(const Complex& c) const {
		return Complex{
			real * c.real - imag * c.imag,
			real * c.imag + c.real * imag
		};
	}

	Complex divide(const Complex& c) const {
		const double cnorm2 = c.real * c.real + c.imag * c.imag;
		return Complex{
			( real * c.real + imag * c.imag) / cnorm2,
			(-real * c.imag + c.real * imag) / cnorm2
		};
	}

	Complex negate() const {
		return Complex{-real, -imag};
	}

	Complex conjugate() const {
		return Complex{real, -imag};
	}
};


// Write a number to an `ostream` (for ex. `std::cout`)
std::ostream& operator <<(std::ostream& os, const Complex& c) {
	const char* sign = c.imag > 0 ? "+" : "-";
	os << c.real << sign << fabs(c.imag) << "i";
	return os;
}


int main() {
	Complex c1{5, 2}, c2{7, -1};

	std::cout << "c1 = " << c1 << ", c2 = " << c2 << std::endl;
	std::cout << std::endl;
	std::cout << c1.add(c2) << std::endl;
	std::cout << c1.sub(c2) << std::endl;
	std::cout << c1.mutiply(c2) << std::endl;
	std::cout << c1.divide(c2) << std::endl;
	std::cout << std::endl;
	std::cout << c1.sub(2) << std::endl;
	std::cout << c1.add(10) << std::endl;
	std::cout << c1.mutiply(3) << std::endl;
	std::cout << c1.divide(1) << std::endl;

	return 0;
}
