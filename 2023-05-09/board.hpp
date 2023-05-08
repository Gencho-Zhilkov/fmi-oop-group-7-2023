#ifndef FMI_OOP_BOARD_HPP
#define FMI_OOP_BOARD_HPP

#include <cassert>

#include "position.hpp"
#include "figure.hpp"


class Board {
private:
    Figure* board[BOARD_SIZE][BOARD_SIZE];

public:
    Board(): board() {}

    Board(const Board& that) = delete;
    Board& operator=(const Board& that) = delete;

    ~Board() {
        for (size_t i = 0; i < BOARD_SIZE; i++) {
            for (size_t j = 0; j < BOARD_SIZE; j++) {
                delete board[i][j];
            }
        }
    }

    Figure* getFigureAt(const Position& position) const {
        return board[position.getRow()][position.getColumn()];
    }

    bool isEmpty(const Position& position) const {
        return getFigureAt(position) == nullptr;
    }

    void addFigureAt(Figure* figure, const Position& position) {
        assert(figure != nullptr);
    	assert(isEmpty(position));
    	board[position.getRow()][position.getColumn()] = figure;
    }

    void removeFigureFrom(const Position& position) {
    	assert(!isEmpty(position));
    	board[position.getRow()][position.getColumn()] = nullptr;
    }

    void moveFigure(const Position& source, const Position& destination) {
        Figure* dstFigure = getFigureAt(destination);
        if (dstFigure != nullptr) {
            removeFigureFrom(destination);
            delete dstFigure;
        }

        Figure* srcFigure = getFigureAt(source);
        removeFigureFrom(source);
        addFigureAt(srcFigure, destination);
    }
};

#endif /* FMI_OOP_BOARD_HPP */
