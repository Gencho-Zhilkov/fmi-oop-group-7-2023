#ifndef FMI_OOP_CAR_HPP
#define FMI_OOP_CAR_HPP

#include <cstring>
#include <climits>
#include <stdexcept>
#include <iostream>

#include "reservation.hpp"


class Car {
private:
	int id;
	char type[51]; // +1 символ за терминиращата '\0'
	int year;
	size_t numReservations;
	Reservation *reservations;

	void setCarData(const int id, const char *type, const int year) {
		if (strlen(type) > 50) {
			throw std::invalid_argument("Car type too long!");
		}

		this->id = id;
		strcpy(this->type, type);
		this->year = year;
		this->numReservations = 0;
		this->reservations = nullptr;
	}

	void copyReservations(const Car& that) {
		numReservations = that.numReservations;
		reservations = new Reservation[numReservations];

		for(size_t i = 0; i < numReservations; i ++) {
			reservations[i] = that.reservations[i];
		}
	}

	void moveReservations(Car&& that) {
		this->reservations = that.reservations;
		this->numReservations = that.numReservations;
		that.numReservations = 0;
		that.reservations = nullptr;
	}

	void cleanup() {
		delete[] reservations;
	}

    friend std::ostream& operator <<(std::ostream &out, const Car& car);
    friend std::istream& operator >>(std::istream &in,  Car& car);

public:
	Car(const int id=-1, const char *type="", const int year=0) {
		setCarData(id, type, year);
	}

	Car(const Car& that) {
		setCarData(that.id, that.type, that.year);
		copyReservations(that);
	}

	Car(Car&& that) {
		setCarData(that.id, that.type, that.year);
		moveReservations(std::move(that));
	}

	Car& operator =(const Car& that) {
		if (this != &that) {
			cleanup();
			setCarData(that.id, that.type, that.year);
			copyReservations(that);
		}

		return *this;
	}

	Car& operator =(Car&& that) {
		if (this != &that) {
			cleanup();
			setCarData(that.id, that.type, that.year);
			moveReservations(std::move(that));
		}

		return *this;
	}

	~Car() {
		cleanup();
	}

	int getId() const {
		return id;
	}

	void assertNotOverlapping(const Reservation& r) {
		for (size_t i = 0; i < numReservations; i ++) {
			if (reservations[i].overlaps(r)) {
				throw std::runtime_error("Reservations overlap!");
			}
		}
	}

	void addReservation(const Reservation& r) {
		// Проверяваме, че новата резервация не е в
		// конфликт с никоя от вече съществуващите.
		assertNotOverlapping(r);

		// Заделяме памет и копираме старите в новите
		Reservation *newReservations = new Reservation[numReservations + 1];
		for (size_t i = 0; i < numReservations; i ++) {
			newReservations[i] = reservations[i];
		}
		// Добавяме новата резервация в края.
		newReservations[numReservations] = r;
		// освобождаваме паметта за старите резервации
		cleanup();
		// пренасочваме указателя към новите
		reservations = newReservations;
		// инкрементираме броя
		numReservations ++;
	}
};

std::ostream& operator <<(std::ostream& out, const Car& car) {
	out << car.id << ' '
		<< car.type << ' '
		<< car.year << ' '
		<< car.numReservations;

	for (size_t i = 0; i < car.numReservations; i++) {
		out << ' ' << car.reservations[i];
	}

	return out;
}

std::istream& operator>>(std::istream& in, Car& car) {
	int id, year;
	char type[51] = "";

	in >> id >> type >> year;

	// По този начин форсираме извикването на оператора за
	// присвояване, който изчиства динамично-заделената памет
	car = Car(id, type, year);

	in >> car.numReservations;
	car.reservations = new Reservation[car.numReservations];
	for (size_t i = 0; i < car.numReservations; i++) {
		in >> car.reservations[i];
	}

	return in;
}

#endif /* FMI_OOP_CAR_HPP */
