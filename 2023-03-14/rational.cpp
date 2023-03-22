#include <iostream>
#include <stdexcept>
#include <cassert>


int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}


class Rational {

private:
	int num;
	int denom;

	// Declared "friend" to be able to access the number's private state!
	// Arithmetic operators
	friend Rational operator +(const Rational& left, const Rational& right);
	friend Rational operator -(const Rational& left, const Rational& right);
	friend Rational operator *(const Rational& left, const Rational& right);
	friend Rational operator /(const Rational& left, const Rational& right);

	// Comparison operators
	friend bool operator ==(const Rational& left, const Rational& right);
	friend bool operator !=(const Rational& left, const Rational& right);
	friend bool operator <(const Rational& left, const Rational& right);
	friend bool operator <=(const Rational& left, const Rational& right);
	friend bool operator >=(const Rational& left, const Rational& right);
	friend bool operator >(const Rational& left, const Rational& right);

	// Write a number to a stream (for ex. `std::cout`)
	friend std::ostream& operator <<(std::ostream& os, const Rational& r);

public:
	// Constructor: it can be called with 0, 1, or 2 arguments!.
	Rational(const int num=0, const int denom=1) {
		const int f = gcd(num, denom);
		this->num = num / f;
		this->denom = denom / f;

		if (denom == 0) {
			throw std::invalid_argument("Denominator cannot be 0!");
		} else if (denom < 0) {
			// Sign information is carried by the num,
			// so switch the signs of both `num` and `denom`.
			this->num *= -1;
			this->denom *= -1;
		}
	}

	// Default copy ctor, assignment operator, and destructor
	Rational(const Rational&) = default;
	Rational& operator =(const Rational&) = default;
	~Rational() = default;
};


// Arithmetic opetations
Rational operator +(const Rational& left, const Rational& right) {
	return Rational{
		left.num * right.denom + right.num * left.denom,
		left.denom * right.denom
	};
}

Rational operator -(const Rational& left, const Rational& right) {
	return Rational{
		left.num * right.denom - right.num * left.denom,
		left.denom * right.denom
	};
}

Rational operator *(const Rational& left, const Rational& right) {
	return Rational{
		left.num * right.num,
		left.denom * right.denom
	};
}

Rational operator /(const Rational& left, const Rational& right) {
	return Rational{
		left.num * right.denom,
		right.num * left.denom
	};
}


// Comparison operators
bool operator ==(const Rational& left, const Rational& right) {
	return left.num == right.num && left.denom == right.denom;
}

bool operator !=(const Rational& left, const Rational& right) {
	return !(left == right);
}

bool operator <(const Rational& left, const Rational& right) {
	const int l = left.num * right.denom;
	const int r = right.num * left.denom;
	return l < r;
}

bool operator <=(const Rational& left, const Rational& right) {
	const int l = left.num * right.denom;
	const int r = right.num * left.denom;
	return l <= r;
}

bool operator >=(const Rational& left, const Rational& right) {
	return !(left < right);
}

bool operator >(const Rational& left, const Rational& right) {
	return !(left <= right);
}


// Write a number to an `ostream` (for ex. `std::cout`)
std::ostream& operator <<(std::ostream& os, const Rational& r) {
	os << r.num << '/' << r.denom;
	return os;
}


int main() {
	Rational r1{7, 2}, r2{2, 5};

	std::cout << "r1 = " << r1 << ", r2 = " << r2 << std::endl;
	std::cout << std::endl;
	std::cout << "r1 + r2 = " << r1 + r2 << std::endl;
	std::cout << "r1 - r2 = " << r1 - r2 << std::endl;
	std::cout << "r1 * r2 = " << r1 * r2 << std::endl;
	std::cout << "r1 / r2 = " << r1 / r2 << std::endl;
	std::cout << std::endl;
	std::cout << "r1 + 1 = " << r1 + 1 << std::endl;
	std::cout << "r1 - 2 = " << r1 - 2 << std::endl;
	std::cout << "r1 * 3 = " << r1 * 3 << std::endl;
	std::cout << "r1 / 4 = " << r1 / 4 << std::endl;
	std::cout << std::endl;
	std::cout << "1 + r1 = " << 1 + r1 << std::endl;
	std::cout << "2 - r1 = " << 2 - r1 << std::endl;
	std::cout << "3 * r1 = " << 3 * r1 << std::endl;
	std::cout << "4 / r1 = " << 4 / r1 << std::endl;
	std::cout << std::endl;
	std::cout << "r1 == r1 = " << (r1 == r1) << std::endl;
	std::cout << "r2 == r2 = " << (r2 == r2) << std::endl;
	std::cout << "r1 == r2 = " << (r1 == r2) << std::endl;
	std::cout << "r1 != r2 = " << (r1 != r2) << std::endl;
	std::cout << std::endl;
	std::cout << "r1 < r2 = " << (r1 < r2) << std::endl;
	std::cout << "r1 <= r2 = " << (r1 <= r2) << std::endl;
	std::cout << "r1 >= r2 = " << (r1 >= r2) << std::endl;
	std::cout << "r1 > r2 = " << (r1 > r2) << std::endl;

	return 0;
}
