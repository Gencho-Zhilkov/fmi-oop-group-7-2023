#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <cassert>


class A {
public:
	virtual void f() const {
		std::cout << "A" << std::endl;
	}
};

class B: public A {
public:
	void f() const {
		std::cout << "B" << std::endl;
	}
};

class C: public B {
public:
	void f() const {
		std::cout << "C" << std::endl;
	}
};


int main() {
	// Стакова променлива от типа на наследника.
	// Променя ли се резултата в зависимост от това дали
	// f() е декларирана като `virtual`? Какъв е типът
	// свързване: статично или динамично?
	{
		A a;
		B b;
		C c;
		a.f();
		b.f();
		c.f();
	}

	// Стакова променлива от базовия тип.
	// Променя ли се резултата в зависимост от това дали
	// f() е декларирана като `virtual`? Какъв е типът
	// свързване: статично или динамично? Какво се случва
	// при инициализирането на 3-те променливи?
	{
		A a = A();
		A b = B();
		A c = C();
		a.f();
		b.f();
		c.f();
	}

	// Използване на указател от типа на наследника.
	// Променя ли се резултата в зависимост от това дали
	// f() е декларирана като `virtual`?
	{
		A* a = new A();
		B* b = new B();
		C* c = new C();
		a->f();
		b->f();
		c->f();
	}

	// Използване на указател от базовия тип.
	// Какво се случва, когато f() е декларирана като `virtual`?
	// Какво се случва, когато не е?
	{
		A* a = new A();
		A* b = new B();
		A* c = new C();
		a->f();
		b->f();
		c->f();
	}

	return 0;
}
