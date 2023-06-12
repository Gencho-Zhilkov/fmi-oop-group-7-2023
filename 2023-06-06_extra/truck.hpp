#ifndef FMI_OOP_TRUCK_HPP
#define FMI_OOP_TRUCK_HPP
#include <iostream>
#include <stdexcept>
#include "vehicle.hpp"


class Truck: public virtual Vehicle {
private:
	static constexpr double KM_PER_KG = 1;

protected:
	double currentLoad;
	double loadCapacity;

public:
	Truck(const char* const model, const double range, const double capacity):
		Vehicle(model, range),
		currentLoad(0), loadCapacity(capacity) {}


	double getRange() const override {
		return maxRange - KM_PER_KG * currentLoad;
	}

	void load(const double load) {
		if (currentLoad + load > loadCapacity) {
			throw std::out_of_range("Will overload capacity!");
		}

		currentLoad += load;
	}

	void unload(const double load) {
		if (currentLoad < load) {
			throw std::out_of_range("Trying to unload too much!");
		}

		currentLoad -= load;
	}

	void print(std::ostream& out) const override {
		out << "TRUCK model: " << model
			<< ", range: " << getRange() << "/" << maxRange
			<< ", load: " << currentLoad << "/" << loadCapacity;
	}
};

#endif /* FMI_OOP_TRUCK_HPP */
