#pragma once
#include <FL/Fl.H>
#include <array>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

static constexpr auto GRID_ROWS = 4;
static constexpr auto GRID_COLS = 4;
static constexpr auto WIDTH = 100 * GRID_COLS;
static constexpr auto HEIGHT = 100 * GRID_ROWS;
static constexpr auto THICKNESS = 5;
static constexpr auto BACKGROUND_COLOR = 0x171717;
static constexpr auto LINE_COLOR = 0x2F2F2F;

// there are 11 possible tile colors
const std::array<Fl_Color, 11> TILE_COLORS = {
    0x2d4f67,
    0x1e3d5a,
    0x0f2c4d,
    0x001b40,
    0x3d5a80,
    0x2e4773,
    0x1f3466,
    0x102259,
    0x4d6d99,
    0x3e5a8c,
    0x2f4780
};


namespace Game {
    class MainWindow : public Fl_Window {
    public:
        MainWindow();
        int play();

    private:
        std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{{0}}};
        std::vector<std::pair<int, int>> emptyTiles;

        int handle(int event) override;
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void printBoard();
        void removeEmptyTile(int, int);
        void addEmptyTile(int, int);
        void draw() override;
        void drawTile(int, int);
        void drawGrid();
        void spawnTile();
    };
}

