//
// Created by Dexxy on 04-02-2026.
//

#include "../include/Piece.h"
#include<utility>

static const int SHAPES[7][PIECE_SIZE][PIECE_SIZE] = {
    // I
    {
             {0,0,0,0},
             {1,1,1,1},
             {0,0,0,0},
             {0,0,0,0}
    },
    // O
    {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
    },
    // T
    {
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
    },
    // L
    {
            {1,0,0,0},
            {1,0,0,0},
            {1,1,0,0},
            {0,0,0,0}
    },
    // J
    {
            {0,1,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {0,0,0,0}
    },
    // S
    {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
    },
    // Z
    {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
    }
};


Piece::Piece(int type) {
    x = BOARD_WIDTH / 2 - 2;
    y = 0;

    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            shape[i][j] = SHAPES[type][i][j];
        }
    }
}

void Piece::RotateL() {
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = i + 1; j < PIECE_SIZE; j++) {
            std::swap(shape[i][j], shape[j][i]);
        }
    }
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE / 2; j++) {
            std::swap(shape[j][i], shape[PIECE_SIZE - 1 - j][i]);
        }
    }
}

void Piece::RotateR() {
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = i + 1; j < PIECE_SIZE; j++) {
            std::swap(shape[i][j], shape[j][i]);
        }
    }
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE / 2; j++) {
            std::swap(shape[i][j], shape[i][PIECE_SIZE - 1 - j]);
        }
    }
}

void Piece::Normalize() {
    int row_offest = 4;
    int col_offset = 4;

    for(int i = 0; i < PIECE_SIZE; i++) {
        for(int j = 0; j < PIECE_SIZE; j++) {
            if (shape[i][j] == 1) {
                if (i < row_offest) row_offest = i;
                if (j < col_offset) col_offset = j;
            }
        }
    }

    if (row_offest == 0 && col_offset == 0) return;

    int temp[PIECE_SIZE][PIECE_SIZE] = {0};

    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            if (shape[i][j] == 1) {
                temp[i - row_offest][j - col_offset] = 1;
            }
        }
    }

    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            shape[i][j] = temp[i][j];
        }
    }
}