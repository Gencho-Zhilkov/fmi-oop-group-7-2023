#ifndef FMI_OOP_CAR_DB_HPP
#define FMI_OOP_CAR_DB_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "car.hpp"

/* TODO:
Довършете каноничното представяне на класа `CarDB`.

Бонус: опитайте се да решите задачата като прочeтeте всички
коли от файла и ги запазите в масив (или в `std::vector`) в
конструктора на класа.
*/
class CarDB {
private:
	char* dbFile;

public:
	CarDB(const char *dbFile) {
		const size_t len = strlen(dbFile);
		this->dbFile = new char[len + 1];
		strcpy(this->dbFile, dbFile);
	}

	~CarDB() {
		delete[] dbFile;
	}

	Car search(const int id) {
		std::ifstream fin(this->dbFile);
		if (!fin) {
			throw std::invalid_argument("Could not open file for reading!");
		}

		Car temp;
		while (fin >> temp) {
			if(temp.getId() == id) {
				return temp;
			}
		}
		fin.close();

		throw std::runtime_error("Car not found!");
	}

	void add(const Car& car) {
		std::ifstream fin(this->dbFile);
		if (!fin) {
			throw std::invalid_argument("Could not open file for reading!");
		}

		Car temp;
		while (fin >> temp) {
			if(temp.getId() == car.getId()) {
				throw std::invalid_argument("Car with ID already exists!");
			}
		}
		fin.close();

		std::ofstream fout(this->dbFile, std::ios::app);
		if (!fout) {
			throw std::runtime_error("Could not open file for writing!");
		}

		fout << car << std::endl;
		fout.close();
	}

	void reserve(const int id, const Reservation &r) {
		std::ifstream fin(this->dbFile);
		if (!fin) {
			throw std::invalid_argument("Could not open file for reading!");
		}

		std::vector<Car> cars;
		bool found = false;
		Car temp;
		while (fin >> temp) {
			if(temp.getId() == id) {
				temp.addReservation(r);
				found = true;
			}
			cars.push_back(temp);
		}
		fin.close();

		if (!found) {
			throw std::invalid_argument("Car not found!");
		}

		std::ofstream fout(this->dbFile, std::ios::trunc);
		if (!fout) {
			throw std::runtime_error("Could not open file for writing!");
		}

		for (size_t i = 0; i < cars.size(); i++) {
			fout << cars[i] << std::endl;
		}
		fout.close();
	}
};

#endif /* FMI_OOP_CAR_DB_HPP */
