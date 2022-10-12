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
        MainWindow() : Fl_Window(WIDTH, HEIGHT, "2048") {
            this->color(BACKGROUND_COLOR);
            // fill emptyTiles
            for (int i = 0; i < GRID_ROWS; i++) {
                for (int j = 0; j < GRID_COLS; j++) {
                    emptyTiles.push_back({i, j});
                }
            }
        }

        int play() {
            show();
            spawnTile();
            return Fl::run();
        }

    private:
        std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{{0}}};
        std::vector<std::pair<int, int>> emptyTiles;

        int handle(int event) override {
            if (event == FL_KEYDOWN) {
                auto key = Fl::event_key();
                if (key == FL_Up) {
                    moveUp();
                } else if (key == FL_Down) {
                    moveDown();
                } else if (key == FL_Left) {
                    moveLeft();
                } else if (key == FL_Right) {
                    moveRight();
                }
            }
            // 0 will end the program
            return 1;
        }

        void moveUp() {
            for (int i = 0; i < GRID_COLS; i++) {
                for (int j = 0; j < GRID_ROWS; j++) {
                    if (board[j][i] == 0) {
                        continue;
                    }
                    int k = j;
                    while (k > 0 && board[k - 1][i] == 0) {
                        board[k - 1][i] = board[k][i];
                        board[k][i] = 0;
                        k--;
                        addEmptyTile(k + 1, i);
                        removeEmptyTile(k, i);
                    }
                    if (k > 0 && board[k - 1][i] == board[k][i]) {
                        board[k - 1][i] *= 2;
                        board[k][i] = 0;
                        addEmptyTile(k, i);
                        removeEmptyTile(k + 1, i);
                    }
                }
            }

            spawnTile();
            redraw();
        }

        void moveDown() {
            for (int i = 0; i < GRID_COLS; i++) {
                for (int j = GRID_ROWS - 1; j >= 0; j--) {
                    if (board[j][i] == 0) {
                        continue;
                    }
                    int k = j;
                    while (k < GRID_ROWS - 1 && board[k + 1][i] == 0) {
                        board[k + 1][i] = board[k][i];
                        board[k][i] = 0;
                        k++;
                        addEmptyTile(k - 1, i);
                        removeEmptyTile(k, i);
                    }
                    if (k < GRID_ROWS - 1 && board[k + 1][i] == board[k][i]) {
                        board[k + 1][i] *= 2;
                        board[k][i] = 0;
                        addEmptyTile(k, i);
                        removeEmptyTile(k - 1, i);
                    }
                }
            }

            spawnTile();
            redraw();
        }

        void moveLeft() {
            for (int i = 0; i < GRID_ROWS; i++) {
                for (int j = 0; j < GRID_COLS; j++) {
                    if (board[i][j] == 0) {
                        continue;
                    }
                    int k = j;
                    while (k > 0 && board[i][k - 1] == 0) {
                        board[i][k - 1] = board[i][k];
                        board[i][k] = 0;
                        k--;
                        addEmptyTile(i, k + 1);
                        removeEmptyTile(i, k);
                    }
                    if (k > 0 && board[i][k - 1] == board[i][k]) {
                        board[i][k - 1] *= 2;
                        board[i][k] = 0;
                        addEmptyTile(i, k);
                        removeEmptyTile(i, k + 1);
                    }
                }
            }

            spawnTile();
            redraw();
        }

        void moveRight() {
            for (int i = 0; i < GRID_ROWS; i++) {
                for (int j = GRID_COLS - 1; j >= 0; j--) {
                    if (board[i][j] == 0) {
                        continue;
                    }
                    int k = j;
                    while (k < GRID_COLS - 1 && board[i][k + 1] == 0) {
                        board[i][k + 1] = board[i][k];
                        board[i][k] = 0;
                        k++;
                        addEmptyTile(i, k - 1);
                        removeEmptyTile(i, k);
                    }
                    if (k < GRID_COLS - 1 && board[i][k + 1] == board[i][k]) {
                        board[i][k + 1] *= 2;
                        board[i][k] = 0;
                        addEmptyTile(i, k);
                        removeEmptyTile(i, k - 1);
                    }
                }
            }

            spawnTile();
            redraw();
        }

        void printBoard() {
            for (int i = 0; i < GRID_ROWS; i++) {
                for (int j = 0; j < GRID_COLS; j++) {
                    std::cout << std::setw(4) << board[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        void removeEmptyTile(int row, int col) {
            for (auto it = emptyTiles.begin(); it != emptyTiles.end(); it++) {
                if (it->first == row && it->second == col) {
                    emptyTiles.erase(it);
                    break;
                }
            }
        }

        void addEmptyTile(int row, int col) {
            emptyTiles.push_back({row, col});
        }

        void draw() override {
            Fl_Window::draw();
            printBoard();
            for (int i = 0; i < GRID_ROWS; i++) {
                for (int j = 0; j < GRID_COLS; j++) {
                    drawTile(i, j);
                    drawGrid();
                }
            }
        }

        void drawTile(int i, int j) {
            Fl_Color color;
            auto boardValue = board[i][j];
            if (boardValue == 0) {
                return;
            }

            // the color of the tile is determined by the log base 2 of the value
            // this is because the value doubles every time you merge
            // so the color should also double
            auto colorIndex = static_cast<int>(log2(boardValue));
            color = TILE_COLORS[colorIndex];

            fl_color(color);
            fl_rectf(
                100 * j,
                100 * i,
                100,
                100
            );

            fl_color(FL_WHITE);
            fl_font(FL_HELVETICA, 36);
            fl_draw(
                std::to_string(boardValue).c_str(),
                100 * j,
                100 * i,
                100,
                100,
                FL_ALIGN_CENTER
            );
        }

        void drawGrid() {
            fl_color(LINE_COLOR);
            fl_line_style(FL_SOLID, THICKNESS * 2);
            fl_rect(0, 0, WIDTH, HEIGHT);
            fl_line_style(FL_SOLID, THICKNESS);


            for (int i = 1; i < GRID_ROWS; i++) {
                for (int j = 1; j < GRID_COLS; j++) {
                    fl_line(100 * j, 0, 100 * j, HEIGHT);
                    fl_line(0, 100 * i, WIDTH, 100 * i);
                }
            }
        }

        void spawnTile() {
            // if the boards full then return
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

            // remove {x, y} from the list of empty tiles
            removeEmptyTile(x, y);

            board[x][y] = value;
        }
    };
}

