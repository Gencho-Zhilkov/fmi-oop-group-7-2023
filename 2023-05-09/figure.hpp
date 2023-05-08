#ifndef FMI_OOP_CHESS_FIGURE_HPP
#define FMI_OOP_CHESS_FIGURE_HPP

#include <stdexcept>
#include <cassert>

#include "position.hpp"


enum class Color {
	WHITE,
	BLACK,
};

class Board;

class Figure {
private:
	const Color color;

public:
	Figure(Color color): color(color) {}

	// Не забравяйте да декларирате деструктора виртуален,
	// за да се извика правилния деструктор!
	virtual ~Figure() {}

	Color getColor() const {
		return color;
	}

	// TODO: Какви базови методи трябва да декларираме тук?
};

#endif /* FMI_OOP_CHESS_FIGURE_HPP */
