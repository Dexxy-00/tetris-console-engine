//
// Created by Dexxy on 04-02-2026.
//

#ifndef GAME_H
#define GAME_H

#include "../include/Board.h"
#include "../include/Piece.h"
#include <vector>
#include <random>
#include <optional>

class Game {
public:
    Game();
    void run();
    void updateScore(int lines);

private:
    Board board;
    std::optional<Piece> currentPiece;
    bool gameOver;
    int score;
    int level;
    int totalLinesCleared;
    int currGravity;

    void moveLeft();
    void moveRight();
    void rotateLeft();
    void rotateRight();

    // 7 bag util
    std::vector<int> bag;
    int idx;
    std::mt19937 rng; // Random engine
    int nextPiece();
    void refill();

    void spawnPiece();
    void gravity();
    void handleInput();
    void drawHUD() const;
    void render() const;

};

#endif //GAME_H
