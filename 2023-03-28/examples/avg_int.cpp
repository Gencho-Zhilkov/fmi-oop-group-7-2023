#include <iostream>
#include <fstream>


int main() {
	std::ifstream fin("ints.bin", std::ios::in | std::ios::binary);
	if (!fin) {
		std::cerr << "Could not open file for reading!" << std::endl;
		return 1;
	}

	int sum = 0, val;
	size_t count = 0;
	while (fin.read((char *)&val, sizeof(val))) {
		sum += val;
		count ++;
	}

	std::cerr << "Count = " << count << std::endl;
	std::cout << "Average = " << (double)sum / count << std::endl;
	return 0;
}
