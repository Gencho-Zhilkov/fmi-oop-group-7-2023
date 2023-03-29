#ifndef _OOP_BOOK_HPP_
#define _OOP_BOOK_HPP_

#include <iostream>
#include <cstring>


struct Book {
	int serialNumber;
	char *title;

	Book(const int serialNumber, const char *title):
		serialNumber{serialNumber} {
		const size_t len = strlen(title);
		this->title = new char[len + 1];
		strcpy(this->title, title);
	}

	// Конструктор, който прочита (десериализира) книга от входен поток
	Book(std::istream& in) {
		// TODO: Имплементирайте метода
	}

	// TODO: Довършете каноничното представяне на класа `Book`

	// Метод, който записва (сериализира) книга на изходен поток
	void save(std::ostream& out) const {
		// TODO: Имплементирайте метода
	}
};

#endif /* _OOP_BOOK_HPP_ */
