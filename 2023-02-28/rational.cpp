#include <iostream>
#include <stdexcept>
#include <cassert>


class Rational {

private:
	int numerator;
	int denominator;

	// Write a number to a stream (for ex. `std::cout`)
	// Declared "friend" to be able to access the number's private state!
	friend std::ostream& operator <<(std::ostream& os, const Rational& r);

public:
	// Constructor: it can be called with 0, 1, or 2 arguments!.
	Rational(const int num=0, const int denom=1) {
		numerator = num;
		denominator = denom;

		if (denominator == 0) {
			throw std::invalid_argument("Denominator cannot be 0!");
		} else if (denominator < 0) {
			// Sign information is carried by the numerator,
			// so switch the signs of both `numerator` and `denominator`.
			numerator *= -1;
			denominator *= -1;
		}
	}

	// Default copy ctor, assignment operator, and destructor
	Rational(const Rational&) = default;
	Rational& operator =(const Rational&) = default;
	~Rational() = default;

	Rational add(const Rational& r) const {
		return Rational{
			numerator * r.denominator + r.numerator * denominator,
			denominator * r.denominator
		};
	}

	Rational sub(const Rational& r) const {
		return Rational{
			numerator * r.denominator - r.numerator * denominator,
			denominator * r.denominator
		};
	}

	Rational mutiply(const Rational& r) const {
		return Rational{
			numerator * r.numerator,
			denominator * r.denominator
		};
	}

	Rational divide(const Rational& r) const {
		return Rational{
			numerator * r.denominator,
			r.numerator * denominator
		};
	}

	void print() const {
		std::cout << numerator << '/' << denominator;
	}
};


// Write a number to an `ostream` (for ex. `std::cout`)
std::ostream& operator <<(std::ostream& os, const Rational& r) {
	os << r.numerator << '/' << r.denominator;
	return os;
}


int main() {
	Rational r1{7, 2}, r2{2, 5};

	std::cout << "r1 = " << r1 << ", r2 = " << r2 << std::endl;
	std::cout << std::endl;
	std::cout << "r1 + r2 = " << r1.add(r2) << std::endl;
	std::cout << "r1 - r2 = " << r1.sub(r2) << std::endl;
	std::cout << "r1 * r2 = " << r1.mutiply(r2) << std::endl;
	std::cout << "r1 / r2 = " << r1.divide(r2) << std::endl;
	std::cout << std::endl;
	std::cout << "r1 + 1 = " << r1.add(1) << std::endl;
	std::cout << "r1 - 2 = " << r1.sub(2) << std::endl;
	std::cout << "r1 * 3 = " << r1.mutiply(3) << std::endl;
	std::cout << "r1 / 4 = " << r1.divide(4) << std::endl;

	return 0;
}
