#ifndef FMI_OOP_CAR_HPP
#define FMI_OOP_CAR_HPP
#include <iostream>
#include <stdexcept>
#include <cstring>
#include "vehicle.hpp"


class Car: public virtual Vehicle {
private:
	static constexpr double KM_PER_PSG = 100;

protected:
	size_t seats;
	size_t numPassengers;
	char **passengers;

	void addPassenger(const char* const passenger, const size_t i) {
		const size_t len = strlen(passenger);
		passengers[i] = new char[len + 1]; // +1 '\0'
		strncpy(passengers[i], passenger, len);
		numPassengers++;
	}

	void copy(const Car& other) {
		seats = other.seats;
		passengers = new char*[seats];

		for (size_t i = 0; i < seats; i++) {
			if (other.passengers[i]) {
				addPassenger(other.passengers[i], i);
			} else {
				passengers[i] = nullptr;
			}
		}
	}

	void move(Car&& other) {
		seats = other.seats;
		passengers = other.passengers;
		other.seats = 0;
		other.passengers = nullptr;
	}

	void cleanup() {
		for (size_t i = 0; i < seats; i++) {
			delete[] passengers[i];
		}
		delete[] passengers;
	}

public:
	Car(const char* const model, const double range, const size_t seats):
		Vehicle(model, range),
		seats(seats), numPassengers(0), passengers(new char*[seats]{nullptr}) {}

	Car(const Car& other): Vehicle(other) {
		copy(other);
	}

	Car(Car&& other): Vehicle(std::move(other)) {
		move(std::move(other));
	}

	Car& operator=(const Car& other) {
		if (this != &other) {
			cleanup();
			Vehicle::operator=(other);
			copy(other);
		}
		return *this;
	}

	Car& operator=(Car&& other) {
		if (this != &other) {
			cleanup();
			Vehicle::operator=(std::move(other));
			move(std::move(other));
		}
		return *this;
	}

	~Car() {
		cleanup();
	}

	void addPassenger(const char* const passenger) {
		assert(numPassengers <= seats);
		if (numPassengers == seats) {
			throw std::out_of_range("Will overload capacity!");
		}

		for (size_t i = 0; i < seats; i++) {
			if (!passengers[i]) {
				addPassenger(passenger, i);
				return;
			}
		}
	}

	void removePassenger(const char* const passenger) {
		if (numPassengers == 0) {
			throw std::invalid_argument("Car is empty!");
		}

		for (size_t i = 0; i < seats; i++) {
			if (strcmp(passengers[i], passenger) == 0) {
				delete[] passengers[i];
				passengers[i] = nullptr;
				numPassengers--;
				return;
			}
		}

		throw std::invalid_argument("Passenger not found!");
	}

	double getRange() const override {
		return maxRange - KM_PER_PSG * numPassengers;
	}

	void print(std::ostream& out) const override {
		out << "CAR model: " << model
			<< ", range: " << getRange() << "/" << maxRange
			<< std::endl << "Passengers:";

		for (size_t i = 0; i < seats; i++) {
			if (passengers[i]) {
				out << std::endl << passengers[i];
			}
		}
	}
};

#endif /* FMI_OOP_CAR_HPP */
