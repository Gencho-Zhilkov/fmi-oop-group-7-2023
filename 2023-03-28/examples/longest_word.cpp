#include <iostream>
#include <fstream>
#include <cstring>


// Слагаме я на достатъчно голямо число
const size_t MAX_LEN = 1024;

int main() {
	// Отваряме файла за четене
	std::ifstream fin("common_words.txt");
	if (!fin) {
		std::cerr << "Could not open file for reading!" << std::endl;
		return 1;
	}

	char currentWord[MAX_LEN], longestWord[MAX_LEN];
	size_t currentLine = 1, longestLine;

	// Четем ред по ред, докато не стигнем до края
	while (fin.getline(currentWord, MAX_LEN)) {
		if (strlen(currentWord) > strlen(longestWord)) {
			strcpy(longestWord, currentWord);
			longestLine = currentLine;
		}
		currentLine ++;
	}

	std::cout << "Longest word = '" << longestWord
			  << "' on line " << longestLine << std::endl;
	return 0;
}
