#include <iostream>
#include <vector>

#include "employee.hpp"


class Company {
private:
	std::vector<Employee*> employees;

public:
	void addEmployee(Employee* e) {
		// TODO: Check that `employee->id()` is not alredy present!
		employees.push_back(e);
	}

	double salaryExpenses() const {
		double res = 0;
		for (const Employee *employee: employees) {
			res += employee->salary();
		}
		return res;
	}

	~Company() {
		for(Employee *employee: employees) {
			delete employee;
		}
	}
};


int main() {
	Company c;
	c.addEmployee(new SalaryEmployee(1, 10000));
	c.addEmployee(new HourlyEmployee(2, 50, 120));
	c.addEmployee(new CommisionEmployee(3, 2000, 500, 10));
	std::cout << c.salaryExpenses() << std::endl;
	return 0;
}
