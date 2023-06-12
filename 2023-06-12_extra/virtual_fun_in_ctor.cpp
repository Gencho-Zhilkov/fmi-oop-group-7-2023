#include <iostream>


// Пример за извкване на вирт. ф-я в конструктора
// и в деструктора на даден обект.
class A {
public:
	A() {
		foo();
	}

	virtual ~A() {
		foo();
	}

	virtual void foo() {
		std::cout << "A::foo()" << std::endl;
	}
};

class B: public A {
public:
	void foo() override {
		std::cout << "B::foo()" << std::endl;
	}
};



int main() {
	std::cout << "A-object:" << std::endl;
	A *a = new A();
	a->foo();
	delete a;

	std::cout << "B-object:" << std::endl;
	A *b = new B();
	b->foo();
	delete b;

	return 0;
}
