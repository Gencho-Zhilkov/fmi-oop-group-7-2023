#include <iostream>
#include <fstream>
#include <string>


const size_t MAX_LEN = 1024;

int main() {
	// Отваряме файла за четене
	std::ifstream fin("common_words.txt");
	if (!fin) {
		std::cerr << "Could not open file for reading!" << std::endl;
		return 1;
	}

	std::string currentWord, longestWord;
	size_t currentLine = 1, longestLine;

	// Четем ред по ред, докато не стигнем до края
	while (std::getline(fin, currentWord)) {
		if (currentWord.length() > longestWord.length()) {
			longestWord = currentWord;
			longestLine = currentLine;
		}
		currentLine ++;
	}

	std::cout << "Longest word = '" << longestWord
			  << "' on line " << longestLine << std::endl;
	return 0;
}
