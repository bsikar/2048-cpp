#pragma once
#include <array>
#include <vector>

static constexpr auto GRID_ROWS = 4;
static constexpr auto GRID_COLS = 4;
static constexpr auto WIDTH = 100 * GRID_COLS;
static constexpr auto HEIGHT = 100 * GRID_ROWS;
static constexpr auto THICKNESS = 5;

namespace Game {
    class Logic {
    public:
        std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{{0}}};
        std::vector<std::pair<int, int>> emptyTiles;

        Logic();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void printBoard();
        void removeEmptyTile(int, int);
        void addEmptyTile(int, int);
        void spawnTile();
    };
}

