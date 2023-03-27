#include <iostream>
#include <fstream>
#include <iomanip>


int main() {
	int n;
	do {
		std::cin >> n;
	} while (n <= 0);

	// Отваряме файла за писане
	std::ofstream fout("harmonic_series.csv");
	if (!fout) {
		std::cerr << "Could not open file for writing!" << std::endl;
		return 1;
	}

	// Слагаме форматирането на 3 знака след десетичната запетая
	fout << std::fixed << std::setprecision(3);

	double h = 0;
	for (int i = 1; i <= n; i++) {
		h += 1. / i;
		fout << i << ',' << h << std::endl;
	}

	return 0;
}
