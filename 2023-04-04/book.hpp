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
		in.read((char *)&serialNumber, sizeof(serialNumber));

		size_t len;
		in.read((char *)&len, sizeof(len));

		title = new char[len + 1];
		in.read(title, len);
		title[len] = '\0';
	}

	// Kанонично представяне на класа `Book`
	Book(const Book& that):
	serialNumber{that.serialNumber} {
		const size_t len = strlen(that.title);
		title = new char[len + 1];
		strcpy(title, that.title);
	}

	Book& operator =(const Book& that) {
		if (this != &that) {
			serialNumber = that.serialNumber;

			delete[] title;
			const size_t len = strlen(that.title);
			title = new char[len + 1];
			strcpy(title, that.title);
		}
		return *this;
	}

	~Book() {
		delete[] title;
	}

	// Метод, който записва (сериализира) книга на изходен поток
	void save(std::ostream& out) const {
		out.write((char *)&serialNumber, sizeof(serialNumber));

		size_t len = strlen(title);
		out.write((char *)&len, sizeof(len));
		out.write(title, len); // НЕ записваме терминиращата '\0'!
	}
};

#endif /* _OOP_BOOK_HPP_ */
