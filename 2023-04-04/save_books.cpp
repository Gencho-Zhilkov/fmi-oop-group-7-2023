#include <fstream>

#include "book.hpp"

int main() {
	Book myBooks[5] = {
		{1, "Across the River and into the Trees"},
		{2, "For Whom the Bell Tolls"},
		{3, "A Farewell to Arms"},
		{4, "The Sun Also Rises"},
		{5, "A Moveable Feast"},
	};

	// Отворете файла `my_books.bin` за писане в бинарен формат
	// std::ofstream fout = ...

	for (size_t i = 0; i < 5; i++) {
		// Запишете `myBooks[i]` във файла
		// ...
	}

	return 0;
}
