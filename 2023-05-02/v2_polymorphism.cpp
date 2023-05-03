#include <iostream>

#include "employee.hpp"
#include "company.hpp"


int main() {
	Company c;
	c.addEmployee(new SalaryEmployee(1, 10000));
	c.addEmployee(new HourlyEmployee(2, 50, 120));
	c.addEmployee(new CommisionEmployee(3, 2000, 500, 10));
	std::cout << c.salaryExpenses() << std::endl;
	return 0;
}
