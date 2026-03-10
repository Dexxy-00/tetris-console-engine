# Tetris Console Engine

A console-based implementation of the classic Tetris game written in C++.

## Features

- Terminal-based game rendering
- Tetromino movement and collision detection
- Left rotation and right rotation of pieces
- Gravity system that automatically drops pieces
- Line clearing mechanics
- Score tracking system
- Progressive difficulty:
  - Gravity speed increases as the score increases

## Game Mechanics

- Pieces fall automatically due to gravity.
- Players can rotate pieces left or right to fit them into gaps.
- Completing a full row clears the line and increases the score.
- As the score increases, the gravity speed increases periodically, making the game more challenging.

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
