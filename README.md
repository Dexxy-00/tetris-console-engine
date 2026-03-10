# Tetris Console Engine

A console-based implementation of the classic Tetris game written in C++.

## Features

- Terminal-based rendering
- Tetromino movement with collision detection
- Left and right piece rotation
- Gravity system for automatic piece dropping
- Line clearing mechanics
- Score tracking system
- Progressive difficulty (gravity speed increases as score increases)
- **7-bag shuffle algorithm** for fair piece randomization

## Game Mechanics

- Pieces fall automatically due to gravity.
- Players can rotate pieces left or right to fit them into gaps.
- Completing a full row clears the line and increases the score.
- As the score increases, the gravity speed increases periodically, making the game more challenging.

## Piece Generation

The game uses the **7-bag shuffle system**, which is used in modern Tetris implementations.

All seven tetrominoes are placed in a "bag", shuffled, and then dealt one by one.  
Once the bag is empty, a new shuffled bag is generated.

This prevents long droughts of specific pieces and ensures balanced gameplay.

## Project Structure

include/   -> header files  
src/       -> implementation files  

## Build

This project uses CMake.

## Controls

| Key | Action |
|----|------|
| A | Move piece left |
| D | Move piece right |
| Q | Rotate piece left |
| E | Rotate piece right |

## Author

Avyay Sood
