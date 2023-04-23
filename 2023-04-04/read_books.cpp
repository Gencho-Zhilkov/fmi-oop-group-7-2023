#include <fstream>

#include "book.hpp"

int main() {
	// Отворете файла `my_books.bin` за четене в бинарен формат
	std::ifstream fin("my_books.bin", std::ios::in | std::ios::binary);
	if (!fin) {
		std::cerr << "Could not open file for reading!" << std::endl;
		return 1;
	}

	// Проверяваме дали не сме стигнали до края.
	while(fin.peek() != EOF) {
		// Прочетете обекта от `fin` и го отпечатайте на `stdout`.
		Book b{fin};
		std::cout << b.serialNumber << ": " << b.title << std::endl;
	}

	return 0;
}
