cmake_minimum_required(VERSION 3.16)
project(Tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Tetris
        src/main.cpp
        src/Game.cpp
        src/Board.cpp
        src/Piece.cpp
)

target_include_directories(Tetris PRIVATE include)