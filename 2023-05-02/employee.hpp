#ifndef FMI_OOP_EMPLOYEE_HPP
#define FMI_OOP_EMPLOYEE_HPP


class Employee {
private:
	int id;

public:
	Employee(const int id) : id(id) {}

	int getId() const {
		return id;
	}

	virtual double salary() const = 0;

	// Не забравяйте да декларирате деструктора виртуален,
	// за да се извика правилния деструктор!
	virtual ~Employee() {}
};


class SalaryEmployee: public Employee {
private:
	double _salary;

public:
	SalaryEmployee(const int id, const double salary):
		Employee(id),
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
		Employee(id),
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
		Employee(id),
		baseSalary(baseSalary), salePremium(salePremium), numSales(numSales) {}

	double salary() const {
		return baseSalary + salePremium * numSales;
	}
};

#endif /* FMI_OOP_EMPLOYEE_HPP */
