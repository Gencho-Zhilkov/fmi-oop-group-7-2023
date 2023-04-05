#include <iostream>
#include <string>

#include "car_db.hpp"


void prompt() {
	std::cout << "> ";
}

int main() {
	CarDB db("cars.db");

	prompt();
	std::string command;
	while (std::cin >> command) {
		try {
			if (command == "Add") {
				int id, year;
				char type[51];

				std::cin >> id >> type >> year;
				db.add(Car(id, type, year));
			} else if (command == "Search") {
				int id;

				std::cin >> id;
				Car c = db.search(id);
				std::cout << c << std::endl;
			} else if (command == "Reserve") {
				int id;
				Reservation r;

				std::cin >> id >> r;
				db.reserve(id, r);
			} else {
				std::cerr << "Invalid command: " << command << std::endl;
				std::cin.ignore(INT_MAX, '\n');
			}
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}

		prompt();
	}

	return 0;
}
