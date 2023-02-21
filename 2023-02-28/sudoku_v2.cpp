#include <iostream>
#include <fstream>
#include <stdexcept>
#include <bitset>
#include <string>
#include <cassert>


// char ops
bool isDigit(const char c) {
	return c >= '0' && c <= '9';
}

int toDigit(const char c) {
	assert(isDigit(c));
	return c - '0';
}


class Sudoku {

private:
	int sudoku[9][9];
	std::bitset<10> rows[9];
	std::bitset<10> cols[9];
	std::bitset<10> boxes[3][3];

	bool isPermitted(const size_t row, const size_t col, const int val) const {
		assert(row < 9 && col < 9);
		assert(1 <= val && val <= 9);

		return !rows[row][val] && !cols[col][val] && !boxes[row/3][col/3][val];
	}

	void set(const size_t row, const size_t col, const int val) {
		assert(row < 9 && col < 9);
		assert(1 <= val && val <= 9);

		assert(!rows[row][val]);
		rows[row][val] = true;

		assert(!cols[col][val]);
		cols[col][val] = true;

		assert(!boxes[row/3][col/3][val]);
		boxes[row/3][col/3][val] = true;

		sudoku[row][col] = val;
	}

	void clear(const size_t row, const size_t col) {
		assert(row < 9 && col < 9);

		const int oldVal = sudoku[row][col];
		assert(1 <= oldVal && oldVal <= 9);
		sudoku[row][col] = 0;

		assert(rows[row][oldVal]);
		rows[row][oldVal] = false;

		assert(cols[col][oldVal]);
		cols[col][oldVal] = false;

		assert(boxes[row/3][col/3][oldVal]);
		boxes[row/3][col/3][oldVal] = false;
	}

	// Try finding a solution recursively starting from `cell`
	bool solve(const size_t cell) {
		if (cell == 9 * 9) {
			// We've assigned a valid value to all cells: Sudoku is solved!
			return true;
		}

		const size_t row = cell / 9, col = cell % 9;
		if (sudoku[row][col] != 0) {
			// Cell already has a value: Move on to next one...
			return solve(cell + 1);
		}

		// Empty cell: Try out assigning all possible values
		// and see if one leads to a valid solution.
		const std::bitset<10> used = rows[row] | cols[col] | boxes[row/3][col/3];
		for (int val = 1; val <= 9; val++) {
			if (!used[val]) {
				set(row, col, val);
				if (solve(cell + 1)) {
					return true;
				}
				clear(row, col);
			}
		}

		// No valid solution exists, given the values before current cell
		return false;
	}

	// Write a sudoku to an output stream (for ex. `std::cout`)
	// Declared as "friend" to be able to access the sudoku's private state!
	friend std::ostream& operator <<(std::ostream& os, const Sudoku& sudoku);

public:
	// Ctor: this gets called when a new `Sudoku` object is created
	// Fills sudoku from `line`. Empty cells are denoted by `.` or `0`.
	Sudoku(const std::string line) {
		if (line.length() != 9 * 9) {
			throw std::invalid_argument("Invalid input length!");
		}

		for (size_t i = 0; i < 9; i++) {
			for (size_t j = 0; j < 9; j++) {
				const char c = line[9 * i + j];
				if (c == '.') {
					sudoku[i][j] = 0;
				} else if (isDigit(c)) {
					const int val = toDigit(c);
					if (!isPermitted(i, j, val)) {
						throw std::invalid_argument("Duplicate value!");
					}
					set(i, j, val);
				} else {
					throw std::invalid_argument("Invalid cell value!");
				}
			}
		}
	}

	// Forbid copying and reassignment
	Sudoku(const Sudoku&) = delete;
	Sudoku& operator =(const Sudoku&) = delete;

	// Dtor: gets called when `Sudoku` object gets destroyed
	// Use default dtor generated by the compiler.
	~Sudoku() = default;

	// Try solving the sudoku.
	void solve() {
		bool solved = solve(0);
		if (!solved) {
			throw std::runtime_error("No solution found!");
		}
	}
};


// Pretty-print a sudoku on output stream `os`
std::ostream& operator <<(std::ostream& os, const Sudoku& sudoku) {
	for (size_t i = 0; i < 9; i++) {
		if (i == 3 || i == 6) {
			os << " ------+-------+------" << std::endl;
		}
		for (size_t j = 0; j < 9; j++) {
			if (j == 3 || j == 6) {
				os << " |";
			}
			const int val = sudoku.sudoku[i][j];
			const char c = val ? val + '0': '.';
			os << ' ' << c;
		}
		os << std::endl;
	}
	return os;
}


// You can find some puzzles at:   https://norvig.com/top95.txt
// Corresponding solutions are at: https://norvig.com/top95solutions.html
int main() {
	std::string line;
	std::cout << "> ";
	while (std::getline(std::cin, line)) {
		try {
			Sudoku sudoku(line);
			std::cout << sudoku << std::endl;
			sudoku.solve();
			std::cout << sudoku << std::endl;
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		std::cout << "> ";
	}

	return 0;
}