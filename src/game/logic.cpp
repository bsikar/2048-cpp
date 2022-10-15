#include "logic.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

Game::Logic::Logic() {
    // fill emptyTiles
    for (auto i = 0; i < GRID_ROWS; i++) {
        for (auto j = 0; j < GRID_COLS; j++) {
            emptyTiles.push_back({i, j});
        }
    }

    // initialize the board with two random tiles
    spawnTile();
    spawnTile();
}


void Game::Logic::moveUp() {
    for (auto col = 0; col < GRID_COLS; ++col) {
        for (auto row = 0; row < GRID_ROWS; ++row) {
            if (board[row][col] == 0) {
                continue;
            }

            auto newRow = row;
            while (newRow > 0 && board[newRow - 1][col] == 0) {
                board[newRow - 1][col] = board[newRow][col];
                board[newRow][col] = 0;
                newRow--;
            }

            if (newRow > 0 && board[newRow - 1][col] == board[newRow][col]) {
                board[newRow - 1][col] *= 2;
                board[newRow][col] = 0;
            }
        }
    }
}

void Game::Logic::moveDown() {
    for (auto col = 0; col < GRID_COLS; ++col) {
        for (auto row = GRID_ROWS - 1; row >= 0; --row) {
            if (board[row][col] == 0) {
                continue;
            }

            auto newRow = row;
            while (newRow < GRID_ROWS - 1 && board[newRow + 1][col] == 0) {
                board[newRow + 1][col] = board[newRow][col];
                board[newRow][col] = 0;
                newRow++;
            }

            if (newRow < GRID_ROWS - 1 && board[newRow + 1][col] == board[newRow][col]) {
                board[newRow + 1][col] *= 2;
                board[newRow][col] = 0;
            }
        }
    }
}

void Game::Logic::moveLeft() {
    for (auto row = 0; row < GRID_ROWS; ++row) {
        for (auto col = 0; col < GRID_COLS; ++col) {
            if (board[row][col] == 0) {
                continue;
            }

            auto newCol = col;
            while (newCol > 0 && board[row][newCol - 1] == 0) {
                board[row][newCol - 1] = board[row][newCol];
                board[row][newCol] = 0;
                newCol--;
            }

            if (newCol > 0 && board[row][newCol - 1] == board[row][newCol]) {
                board[row][newCol - 1] *= 2;
                board[row][newCol] = 0;
            }
        }
    }
}

void Game::Logic::moveRight() {
    for (auto row = 0; row < GRID_ROWS; ++row) {
        for (auto col = GRID_COLS - 1; col >= 0; --col) {
            if (board[row][col] == 0) {
                continue;
            }

            auto newCol = col;
            while (newCol < GRID_COLS - 1 && board[row][newCol + 1] == 0) {
                board[row][newCol + 1] = board[row][newCol];
                board[row][newCol] = 0;
                newCol++;
            }

            if (newCol < GRID_COLS - 1 && board[row][newCol + 1] == board[row][newCol]) {
                board[row][newCol + 1] *= 2;
                board[row][newCol] = 0;
            }
        }
    }
}

void Game::Logic::spawnTile() {
    for (auto row = 0; row < GRID_ROWS; ++row) {
        for (auto col = 0; col < GRID_COLS; ++col) {
            if (board[row][col] == 0) {
                emptyTiles.emplace_back(row, col);
            }
        }
    }

    if (emptyTiles.empty()) {
        return;
    }

    int value = rand() % 2 == 0 ? 2 : 4;

    // get a random row and column thats in emptyTile
    std::vector<std::pair<int, int>> pair;
    std::sample(
        emptyTiles.begin(),
        emptyTiles.end(),
        std::back_inserter(pair),
        1,
        std::mt19937{ std::random_device{}() }
    );
    auto x = pair[0].first;
    auto y = pair[0].second;

    board[x][y] = value;
}

void Game::Logic::printBoard() {
    for (auto i = 0; i < GRID_ROWS; i++) {
        for (auto j = 0; j < GRID_COLS; j++) {
            std::cout << std::setw(4) << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

