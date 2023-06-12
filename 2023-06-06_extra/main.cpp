#include <iostream>
#include <fstream>
#include <stdexcept>

#include "vehicle.hpp"
#include "car.hpp"
#include "truck.hpp"
#include "pickup_truck.hpp"


void storeVehicles(const std::vector<Vehicle*>& vehicles, const std::string& filename) {
	// TODO: check if file already exists!

	std::ofstream fout(filename);
	if (!fout) {
		throw std::runtime_error("Could not open file for writing!");
	}

	for (const Vehicle *v : vehicles) {
		fout << *v << std::endl;
	}

	// make Nora happy!
	fout.close();
}

int main() {
	Car car("Renault", 1000, 5);
	car.addPassenger("Some bloke");
	car.addPassenger("Ivan Vazov");
	car.addPassenger("Some other bloke");
	car.removePassenger("Some bloke");

	Truck truck("Volvo", 2000, 1000);
	truck.load(135);
	truck.unload(40);
	truck.load(105);

	PickupTruck pickup("Ford", 1500, 4, 500);
	pickup.addPassenger("Some dude");
	pickup.setSchedule({"Get groceries", "Pickup kids", "Go home"});
	pickup.load(100);

	const char* task1 = pickup.getNextTask();
	std::cout << "Finished task: " << task1 << std::endl;
	delete[] task1;

	std::vector<Vehicle*> vehicles = { &car, &truck, &pickup };
	for (const Vehicle *v : vehicles) {
		std::cout << *v << std::endl;
	}

	storeVehicles(vehicles, "vehicles.txt");

	return 0;
}
