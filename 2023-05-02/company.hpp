#ifndef FMI_OOP_COMPANY_HPP
#define FMI_OOP_COMPANY_HPP

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

#endif /* FMI_OOP_COMPANY_HPP */
