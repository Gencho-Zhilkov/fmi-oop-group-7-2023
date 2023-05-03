// Повече информация за smart pointers може да намерите тук:
// https://en.cppreference.com/book/intro/smart_pointers
// или тук:
// https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170
#include <iostream>
#include <vector>
#include <memory>	// Header for "smart" pointers.

#include "employee.hpp"


/**
 * Ре-имплементация на Company, която, вместо `Employee*`,
 * изпозлва `std::shared_ptr<Employee>`.
 *
 * Забележете, че вече няма нужда да дефинираме деструктор, който
 * екплицитно да освобождава паметта на всеки от елементите!
 */
class Company {
private:
	std::vector<std::shared_ptr<Employee>> employees;

public:
	void addEmployee(const std::shared_ptr<Employee>& employee) {
		// TODO: Check that `employee->id()` is not alredy present!
		employees.push_back(employee);
	}

	double salaryExpenses() const {
		double res = 0;
		for (const auto employee: employees) {
			res += employee->salary();
		}
		return res;
	}
};


int main() {
	Company c;
	c.addEmployee(std::make_shared<SalaryEmployee>(1, 10000));
	c.addEmployee(std::make_shared<HourlyEmployee>(2, 50, 120));
	c.addEmployee(std::make_shared<CommisionEmployee>(3, 2000, 500, 10));
	std::cout << c.salaryExpenses() << std::endl;
	return 0;
}
