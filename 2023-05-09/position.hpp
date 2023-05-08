#ifndef FMI_OOP_CHESS_POSITION_HPP
#define FMI_OOP_CHESS_POSITION_HPP

#include <cstddef>
#include <cassert>
#include <cmath>
#include <vector>


const size_t BOARD_SIZE = 8;

class Position {
private:
    const size_t row;
    const size_t column;

public:
	Position(const size_t row, const size_t column):
		row(row), column(column) {}

    Position(const char rank, const char file):
        Position{(size_t)(rank - 'A'), (size_t)(file - '0')} {}

    size_t getRow() const {
        return row;
    }

    size_t getColumn() const {
        return column;
    }

    bool isValid() const {
        return (row < BOARD_SIZE) and (column < BOARD_SIZE);
    }

    bool operator==(const Position& other) const {
        return (row == other.row) and (column == other.column);
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};


// Клас с помощни функции за провекра дали две позиции
// се намират на един и същи ред, колона или диагонал,
// както и за генериране на позициите между двете.
class Segment {
private:
    const Position start;
    const Position end;

    int sign(const int x) const {
        return (x > 0) - (x < 0);
    }

public:
    Segment(const Position& start, const Position& end):
        start(start), end(end) {
        assert (start != end);
    }

    bool isRow() const {
        return start.getRow() == end.getRow();
    }

    bool isColumn() const {
        return start.getColumn() == end.getColumn();
    }

    bool isDiagonal() const {
        const size_t rowDist = abs(start.getRow() - end.getRow());
        const size_t colDist = abs(start.getColumn() - end.getColumn());
        return rowDist == colDist;
    }

    std::vector<Position> inBetween() const {
        assert (isRow() || isColumn() || isDiagonal());

        const size_t r0 = start.getRow();
        const size_t r1 = end.getRow();
        const int dr = sign(r1 - r0);

        const size_t c0 = start.getColumn();
        const size_t c1 = end.getColumn();
        const int dc = sign(c1 - c0);

        std::vector<Position> result;
        for (size_t r = r0 + dr, c = c0 + dc; r != r1 || c != c1; r += dr, c += dc) {
            result.push_back(Position(r, c));
        }
        return result;
    }
};

#endif /* FMI_OOP_CHESS_POSITION_HPP */
