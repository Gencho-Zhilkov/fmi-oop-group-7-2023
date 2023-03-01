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
	std::cout << std::endl;
	std::cout << "sizeof(S) = " << sizeof(S) << std::endl;
	std::cout << "sizeof(S::sh2) = " << sizeof(S::sh2) << std::endl;
	std::cout << "sizeof(S::str1) = " << sizeof(S::str1) << std::endl;
	std::cout << "sizeof(S::dbl) = " << sizeof(S::dbl) << std::endl;
	std::cout << std::endl;
	std::cout << "offsetof(l) = " << offsetof(S, l) << std::endl;
	std::cout << "padding ch -> l = "
			  << (offsetof(S, l) - (offsetof(S, ch) + sizeof(S::ch))) << std::endl;
	std::cout << std::endl;
	std::cout << "padding sh2 -> f = "
			  << (offsetof(S, f) - (offsetof(S, sh2) + sizeof(S::sh2))) << std::endl;
	std::cout << std::endl;
	std::cout << "padding after str2 = "
			  << (sizeof(S) - (offsetof(S, str2) + sizeof(S::str2))) << std::endl;
	std::cout << std::endl;

	return 0;
}
