#include <iostream>
#include <fstream>
#include <random>

const size_t N = 1000;
const int RAND_FROM = -1000;
const int RAND_TO = +2000;

int main() {
	std::ofstream fout("ints.bin", std::ios::out | std::ios::binary);
	if (!fout) {
		std::cerr << "Could not open file for writing!" << std::endl;
		return 1;
	}

	// Random-generation C++11 magic, cf:
	// https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range
	std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> dist(RAND_FROM, RAND_TO);

	for (int i = 1; i <= N; i++) {
		const int rand = dist(generator);
		fout.write((char*)&rand, sizeof(rand));
	}

	return 0;
}
