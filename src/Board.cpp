//
// Created by Dexxy on 04-02-2026.
//

#include "../include/Board.h"
#include "../include/Constants.h"

Board::Board() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            grid[i][j] = 0;
        }
    }
}

bool Board::canPlace(const Piece &piece, int nx, int ny) const {
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            if (piece.shape[i][j] == 0) continue;

            int r = ny + i;
            int c = nx + j;

            if (r < 0 || c < 0 || r >= BOARD_HEIGHT || c >= BOARD_WIDTH) return false;

            if (grid[r][c] != 0) return false;
        }
    }
    return true;
}

void Board::lockPiece(const Piece &piece) {
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            if (piece.shape[i][j] == 0) continue;

            int r = piece.y + i;
            int c = piece.x + j;

            if (r >= 0 && c >= 0 && r < BOARD_HEIGHT && c < BOARD_WIDTH)
                grid[r][c] = 1;
        }
    }
}

int Board::clearLines() {
    int count = 0;

    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
        int j;
        for (j = 0; j < BOARD_WIDTH; j++) {
            if (grid[i][j] == 0) break;
        }

        if (j == BOARD_WIDTH) {
            count++;

            // shift rows down
            for (int x = i; x > 0; x--) {
                for (int y = 0; y < BOARD_WIDTH; y++) {
                    grid[x][y] = grid[x - 1][y];
                }
            }

            // clear top row
            for (int y = 0; y < BOARD_WIDTH; y++) {
                grid[0][y] = 0;
            }

            i++;
        }
    }
    return count;
}


int Board::getCell(int row, int col) const {
    if (row < 0 || row >= BOARD_HEIGHT || col < 0 || col >= BOARD_WIDTH) return 0;
    return grid[row][col];
}
