//
// Created by Dexxy on 04-02-2026.
//

#ifndef PIECE_H
#define PIECE_H
#include "Constants.h"

class Piece {
public:
    // Position
    int x;
    int y;

    Piece(int type);

    // Rotation
    void RotateL();
    void RotateR();
    void Normalize();

    // Shape
    int shape[PIECE_SIZE][PIECE_SIZE];
};

#endif //PIECE_H
