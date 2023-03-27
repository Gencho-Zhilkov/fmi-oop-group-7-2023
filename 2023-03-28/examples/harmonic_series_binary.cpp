#include <iostream>
#include <fstream>
#include <iomanip>


int main() {
	int n;
	do {
		std::cin >> n;
	} while (n <= 0);

	std::ofstream fout("harmonic_series.bin", std::ios::out | std::ios::binary);
	if (!fout) {
		std::cerr << "Could not open file for writing!" << std::endl;
		return 1;
	}

	double h = 0;
	for (int i = 1; i <= n; i++) {
		h += 1. / i;
		fout.write((char*)&h, sizeof(h));
	}

	return 0;
}
