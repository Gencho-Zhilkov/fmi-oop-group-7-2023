#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <cassert>
#include <string>

// 01/01/1981,20.7
struct Record {
	int day, month, year;
	double temp;
};

std::istream& operator>>(std::istream& is, Record& r) {
	is >> r.day;
	is.ignore(1, '/');
	is >> r.month;
	is.ignore(1, '/');
	is >> r.year;
	is.ignore(1, ',');
	is >> r.temp;
	is.ignore(-1u, '\n');
	return is;
}

std::ostream& operator<<(std::ostream& os, const Record& r) {
	os << r.day << '/' << r.month << '/' << r.year << ',' << r.temp;
	return os;
}

struct YearlyStats {
	int year;
	double sum;
	size_t count;
	Record min;
	Record max;

	YearlyStats(const Record& r):
		year{r.year}, sum{r.temp}, count{1}, min{r}, max{r} {}

	double avgTemp() const {
		return sum / count;
	}

	void addRecort(const Record& r) {
		assert (r.year == year);

		sum += r.temp;
		count ++;
		if (r.temp < min.temp) {
			min = r;
		}
		if (r.temp > min.temp) {
			max = r;
		}
	}
};

std::ostream& operator<<(std::ostream& os, const YearlyStats& st) {
	os << st.year << ',' << st.count << ',' << st.avgTemp()
	   << st.min << ',' << st.max;
	return os;
}


int main() {
	std::ifstream fin("temperature.csv");
	if (!fin) {
		std::cerr << "Could not open file for reading!" << std::endl;
		return 1;
	}

	std::ofstream fout("result.csv");
	if (!fout) {
		std::cerr << "Could not open file for writing!" << std::endl;
		return 2;
	}

	// Ignore first (headers) line
	fin.ignore(-1u, '\n');

	Record r;
	fin >> r;
	if (!fin) {
		std::cerr << "No valid records in file!" << std::endl;
		return 3;
	}

	YearlyStats st{r};

	while (fin >> r) {
		// std::cout << r << std::endl;
		if (r.year == st.year) {
			st.addRecort(r);
		} else {
			std::cout << st << std::endl;
			fout << st << std::endl;
			st = YearlyStats{r};
		}
	}

	return 0;
}
