#include <iostream>
#include <fstream>
#include <iomanip>


int main() {
	int n;
	do {
		std::cin >> n;
	} while (n <= 0);

	std::ofstream fout("harmonic_series.csv");
	if (!fout) {
		std::cerr << "Could not open file for writing!" << std::endl;
		return 1;
	}

	// Set formatting to single digit after the decimal point
	fout << std::fixed << std::setprecision(3);

	for (int i = 1; i <= n; i++) {
		const double d = 1. / i;
		fout << i << ',' << d << std::endl;
	}

	return 0;
}
