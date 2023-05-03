#include <iostream>
#include <stdexcept>
#include <cassert>
#include <vector>


enum class EmployeeType {
	SALARY_EMPLOYEE,
	HOURLY_CONTRACTOR,
	COMMISION_EMPLOYEE,
};

class Employee {
private:
	const int _id;
	const EmployeeType _type;

public:
	Employee(const int id, const EmployeeType& type):
		_id(id), _type(type) {}

	int id() const {
		return _id;
	}

	EmployeeType type() const {
		return _type;
	}

	double salary() const {
		throw std::runtime_error("Not implemented!");
	}
};

class SalaryEmployee: public Employee {
private:
	double _salary;

public:
	SalaryEmployee(const int id, const double salary):
		Employee(id, EmployeeType::SALARY_EMPLOYEE),
		_salary(salary) {}

	double salary() const {
		return _salary;
	}
};

class HourlyEmployee: public Employee {
private:
	double hourlyRate;
	unsigned numHours;

public:
	HourlyEmployee(const int id, const double hourlyRate, const unsigned numHours):
		Employee(id, EmployeeType::HOURLY_CONTRACTOR),
		hourlyRate(hourlyRate), numHours(numHours) {}

	double salary() const {
		return hourlyRate * numHours;
	}
};

class CommisionEmployee: public Employee {
private:
	double baseSalary;
	double salePremium;
	unsigned numSales;

public:
	CommisionEmployee(const int id, const double baseSalary, const double salePremium, const unsigned numSales):
		Employee(id, EmployeeType::COMMISION_EMPLOYEE),
		baseSalary(baseSalary), salePremium(salePremium), numSales(numSales) {}

	double salary() const {
		return baseSalary + salePremium * numSales;
	}
};


class Company {
private:
	std::vector<Employee*> employees;

public:
	void addEmployee(Employee* employee) {
		// TODO: Check that `employee->id()` is not alredy present!
		employees.push_back(employee);
	}

	double salaryExpenses() const {
		double expenses = 0;
		for(const Employee *employee: employees) {
			double employeeSalary;

			switch(employee->type()) {
			case EmployeeType::SALARY_EMPLOYEE:
				employeeSalary = ((SalaryEmployee *)employee)->salary();
				break;
			case EmployeeType::HOURLY_CONTRACTOR:
				employeeSalary = ((HourlyEmployee *)employee)->salary();
				break;
			case EmployeeType::COMMISION_EMPLOYEE:
				employeeSalary = ((CommisionEmployee *)employee)->salary();
				break;
			}

			expenses += employeeSalary;
		}

		return expenses;
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
