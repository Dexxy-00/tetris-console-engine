//
// Created by Dexxy on 04-02-2026.
//

#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"
#include "Constants.h"

class Board {
public:
    Board();

    bool canPlace(const Piece &piece, int nx, int ny) const;
    void lockPiece(const Piece &piece);
    int clearLines();

    int getCell(int row, int col) const;

private:
    int grid[BOARD_HEIGHT][BOARD_WIDTH];
};

#endif //BOARD_H
