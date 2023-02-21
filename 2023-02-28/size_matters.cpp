#include <iostream>
#include <cstddef>


struct Point {
	float x;
	double y;
};

struct S {
	char	ch;
	long	l;
	short	sh1[3];
	char	str1[2];
	double	dbl[2];
	short	sh2[1];
	float	f[3];
	char	str2[3];
};


int main() {
	// Some example calls of `sizeof` and `offsetof`:
	std::cout << "A `Point` object is " << sizeof(Point) << " bytes." << std::endl;
	std::cout << "Its `x` coordinate is " << sizeof(Point::x) << " bytes." << std::endl;
	std::cout << "Its `y` coordinate is " << sizeof(Point::y) << " bytes." << std::endl;
	std::cout << "`x` is at an offset of " << offsetof(Point, x) << " bytes." << std::endl;
	std::cout << "`y` is at an offset of " << offsetof(Point, y) << " bytes." << std::endl;
	std::cout << "There are " << offsetof(Point, y) - (offsetof(Point, x) + sizeof(Point::x))
			  << " bytes of padding between `x` and `y`." << std::endl;

	// Add your code here. Use `sizeof` and `offsetof` to determine the
	// sizes, offsets, and paddings of the different components of `S`.
	// ...
	std::cout << std::endl;
	std::cout << "sizeof(S) = " << sizeof(S) << std::endl;
	std::cout << "sizeof(S::sh2) = " << sizeof(S::sh2) << std::endl;
	std::cout << "sizeof(S::str1) = " << sizeof(S::str1) << std::endl;
	std::cout << "sizeof(S::dbl) = " << sizeof(S::dbl) << std::endl;
	std::cout << std::endl;
	std::cout << "offsetof(ch) = " << offsetof(S, ch) << std::endl;
	std::cout << "sizeof(ch) = " << sizeof(S::ch) << std::endl;
	std::cout << std::endl;
	std::cout << "offsetof(l) = " << offsetof(S, l) << std::endl;
	std::cout << "sizeof(l) = " << sizeof(S::l) << std::endl;
	std::cout << std::endl;
	std::cout << "offsetof(sh1) = " << offsetof(S, sh1) << std::endl;
	std::cout << "sizeof(sh1) = " << sizeof(S::sh1) << std::endl;
	std::cout << std::endl;
	std::cout << "offsetof(str1) = " << offsetof(S, str1) << std::endl;
	std::cout << "sizeof(str1) = " << sizeof(S::str1) << std::endl;
	std::cout << std::endl;
	std::cout << "offsetof(dbl) = " << offsetof(S, dbl) << std::endl;
	std::cout << "sizeof(dbl) = " << sizeof(S::dbl) << std::endl;
	std::cout << std::endl;
	std::cout << "offsetof(sh2) = " << offsetof(S, sh2) << std::endl;
	std::cout << "sizeof(sh2) = " << sizeof(S::sh2) << std::endl;
	std::cout << std::endl;
	std::cout << "offsetof(f) = " << offsetof(S, f) << std::endl;
	std::cout << "sizeof(f) = " << sizeof(S::f) << std::endl;
	std::cout << std::endl;
	std::cout << "offsetof(str2) = " << offsetof(S, str2) << std::endl;
	std::cout << "sizeof(str2) = " << sizeof(S::str2) << std::endl;
	std::cout << std::endl;

	return 0;
}
