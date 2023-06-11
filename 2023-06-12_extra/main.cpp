#include <iostream>
#include <stdexcept>
#include <cstring>


class A {
private:
	size_t size;
	unsigned *array;

public:
	// TODO: your code here!
};

class B: public A {
private:
	bool b;

public:
	// TODO: your code here!
};

class C: public B {
private:
	char *c;

public:
	// TODO: your code here!
};

class D: public A, B {
private:
	double d;

public:
	// TODO: your code here!
};


void save(const A* objects[], const size_t count, const char *file) {
	// TODO: your code here!
}


int main() {
	const A* objects[4] = {
		// TODO: Add appropriate constructors here!
		// new A(),
		// new B(),
		// new C(),
		// new D(),
	};

	save(objects, 4, "objects.txt");

	// TODO: add cleanup code here!

	return 0;
}


