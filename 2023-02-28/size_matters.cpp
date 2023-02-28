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

	return 0;
}
