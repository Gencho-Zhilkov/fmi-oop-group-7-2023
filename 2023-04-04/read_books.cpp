#include <fstream>

#include "book.hpp"

int main() {
	// Отворете файла `my_books.bin` за четене в бинарен формат
	// std::ifstream fin = ...

	// Проверяваме дали не сме стигнали до края.
	while(fin.peek() != EOF) {
		// Прочетете обекта от `fin` и го отпечатайте на `stdout`.
		// ...
	}

	return 0;
}
