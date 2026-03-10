//
// Created by Dexxy on 04-02-2026.
//

#include "../include/Game.h"

#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>
#include <windows.h>
#include <conio.h>

Game::Game() : gameOver(false), idx(0), rng(std::random_device{}()), score(0), level(1), totalLinesCleared(0), currGravity(BASE_GRAVITY_MS) {
    refill();
    spawnPiece();
}

void Game::refill() {
    bag = {0, 1, 2, 3, 4, 5, 6};
    idx = 0;
    std::shuffle(bag.begin(), bag.end(), rng);
}

int Game::nextPiece() {
    if (idx >= bag.size()) refill();
    return bag[idx++];
}

void Game::spawnPiece() {
    int temp = nextPiece();
    currentPiece.emplace(temp);

    if (!board.canPlace(*currentPiece, currentPiece -> x, currentPiece -> y)) {
        gameOver = true;
    }
}

void Game::updateScore(int lines) {
    totalLinesCleared += lines;
    score = score + lines * (level * 100);
    if (totalLinesCleared >= level * 5) {
        level++;

        currGravity = currGravity - (level - 1) * GRAVITY_STEP_MS;
        if (currGravity < MIN_GRAVITY_MS) {
            currGravity = MIN_GRAVITY_MS;
        }
    }
}

void Game::gravity() {
    if (!currentPiece.has_value())
        return;

    if (board.canPlace(*currentPiece, currentPiece -> x, currentPiece -> y + 1)) {
        currentPiece -> y++;
    }
    else {
        board.lockPiece(*currentPiece);
        int lines = board.clearLines();
        if (lines >= 1) updateScore(lines);
        spawnPiece();
    }
}

void reset_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(consoleHandle, coord);
}

void Game::drawHUD() const {
    std::cout << "Score: " << score
              << "            Level: " << level << "\n";
    std::cout << "-----------------------------\n";
}


void Game::render() const {
    reset_cursor();
    drawHUD();

    for (int r = 0; r < BOARD_HEIGHT; r++) {
        for (int c = 0; c < BOARD_WIDTH; c++) {

            bool drawPiece = false;

            if (currentPiece) {
                for (int i = 0; i < PIECE_SIZE; i++) {
                    for (int j = 0; j < PIECE_SIZE; j++) {
                        if (currentPiece->shape[i][j] == 1) {
                            int pr = currentPiece->y + i;
                            int pc = currentPiece->x + j;

                            if (pr == r && pc == c) {
                                drawPiece = true;
                            }
                        }
                    }
                }
            }

            if (drawPiece || board.getCell(r, c)) {
                std::cout << "[ ]";
            } else {
                std::cout << " . ";
            }
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}

void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}


void Game::run() {
    hideCursor();
    spawnPiece();

    auto lastGravity = std::chrono::steady_clock::now();

    while (!gameOver) {
        handleInput();
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastGravity).count();

        if (elapsed > BASE_GRAVITY_MS) {
            gravity();
            lastGravity = now;
        }

        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAMES_MS));
    }
}

void Game::moveRight() {
    if (!currentPiece.has_value()) return;

    Piece temp = *currentPiece;
    temp.x++;

    if (board.canPlace(temp, temp.x, temp.y)) {
        currentPiece = temp;
    }
}

void Game::moveLeft() {
    if (!currentPiece.has_value()) return;

    Piece temp = *currentPiece;
    temp.x--;

    if (board.canPlace(temp, temp.x, temp.y)) {
        currentPiece = temp;
    }
}

void Game::rotateLeft() {
    if (!currentPiece.has_value()) return;

    static const std::vector<std::pair<int, int>> offsets = {{0, 0}, {0, -1}, {1, 0}, {-1, 0}};

    Piece temp = *currentPiece;
    temp.RotateL();
    temp.Normalize();
    for (auto [dx, dy] : offsets) {
        Piece test = temp;
        test.x += dx;
        test.y += dy;
        if (board.canPlace(test, test.x, test.y)) {
            currentPiece = test;
            return;
        }
    }
}

void Game::rotateRight() {
    if (!currentPiece.has_value()) return;

    static const std::vector<std::pair<int, int>> offsets = {{0, 0}, {0, -1}, {1, 0}, {-1, 0}};

    Piece temp = *currentPiece;
    temp.RotateR();
    temp.Normalize();
    for (auto [dx, dy] : offsets) {
        Piece test = temp;
        test.x += dx;
        test.y += dy;
        if (board.canPlace(test, test.x, test.y)) {
            currentPiece = test;
            return;
        }
    }
}

void Game::handleInput() {
    if (!_kbhit()) return;

    char key = _getch();

    switch (key) {
        case 'a': moveLeft(); break;
        case 'd': moveRight(); break;
        case 'q': rotateLeft(); break;
        case 'e': rotateRight(); break;
        case 27: gameOver = true;
    }
}