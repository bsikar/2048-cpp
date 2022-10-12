#pragma once
#include <FL/Fl.H>
#include <array>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include <cmath>

const auto WIDTH = 400;
const auto THICKNESS = 5;
const auto GRID_SIZE = 4;
const auto BACKGROUND_COLOR = 0x171717;
const auto LINE_COLOR = 0x2F2F2F;

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
        MainWindow() : Fl_Window(WIDTH, WIDTH, WIDTH, WIDTH, "2048") {
            this->color(BACKGROUND_COLOR);
            srand(time(NULL));
        }

        int play() {
            show();
            spawnTile();
            return Fl::run();
        }

    private:
        std::array<std::array<int, GRID_SIZE>, GRID_SIZE> board = {{{0}}};

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

        void printBoard() {
            for (int i = 0; i < GRID_SIZE; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
                    std::cout << board[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        void moveUp() {
            // start at 1 to remove top layer
            for (int i = 1; i < GRID_SIZE; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
                    if (board[i][j] == 0) {
                        continue;
                    }

                    // move up until we hit a tile or the top
                    for (int k = i; k > 0; k--) {
                        if (board[k - 1][j] == 0) {
                            board[k - 1][j] = board[k][j];
                            board[k][j] = 0;
                        } else if (board[k - 1][j] == board[k][j]) {
                            board[k - 1][j] *= 2;
                            board[k][j] = 0;
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }

            spawnTile();
            redraw();
        }

        void moveDown() {
            // go to GRID_SIZE - 1 to remove last layer
            for (int i = 0; i < GRID_SIZE - 1; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
                    if (board[i][j] == 0) {
                        continue;
                    }

                    // move down until we hit a tile or the bottom
                    for (int k = i; k < GRID_SIZE; k++) {
                        if (board[k + 1][j] == 0) {
                            board[k + 1][j] = board[k][j];
                            board[k][j] = 0;
                        } else if (board[k + 1][j] == board[k][j]) {
                            board[k + 1][j] *= 2;
                            board[k][j] = 0;
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }

            spawnTile();
            redraw();
        }

        void moveLeft() {
            for (int i = 0; i < GRID_SIZE; i++) {
                // start at 1 to remove right side
                for (int j = 1; j < GRID_SIZE; j++) {
                    if (board[i][j] == 0) {
                        continue;
                    }

                    // move left until we hit a tile or the left
                    for (int k = j; k > 0; k--) {
                        if (board[i][k - 1] == 0) {
                            board[i][k - 1] = board[i][k];
                            board[i][k] = 0;
                        } else if (board[i][k - 1] == board[i][k]) {
                            board[i][k - 1] *= 2;
                            board[i][k] = 0;
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }

            spawnTile();
            redraw();
        }

        void moveRight() {
            for (int i = 0; i < GRID_SIZE; i++) {
                // go to GRID_SIZE - 1 to remove the left side
                for (int j = 0; j < GRID_SIZE - 1; j++) {
                    if (board[i][j] == 0) {
                        continue;
                    }

                    // move right until we hit a tile or the right
                    for (int k = j; k < GRID_SIZE; k++) {
                        if (board[i][k + 1] == 0) {
                            board[i][k + 1] = board[i][k];
                            board[i][k] = 0;
                        } else if (board[i][k + 1] == board[i][k]) {
                            board[i][k + 1] *= 2;
                            board[i][k] = 0;
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }

            spawnTile();
            redraw();
        }

        void draw() override {
            Fl_Window::draw();
            for (int i = 0; i < GRID_SIZE; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
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
            fl_rect(0, 0, WIDTH, WIDTH);
            fl_line_style(FL_SOLID, THICKNESS);

            for (int i = 1; i < GRID_SIZE; i++) {
                fl_line(100 * i, 0, 100 * i, WIDTH);
                fl_line(0, 100 * i, WIDTH, 100 * i);
            }
        }

        bool isFull() {
            for (int i = 0; i < GRID_SIZE; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
                    if (board[i][j] == 0) {
                        return false;
                    }
                }
            }

            return true;
        }

        void spawnTile() {
            // if the boards full then return
            if (isFull()) {
                return;
            }

            int x = rand() % GRID_SIZE;
            int y = rand() % GRID_SIZE;
            int value = rand() % 2 == 0 ? 2 : 4;
            // if the tile is already occupied, try again
            if (board[x][y] != 0) {
                spawnTile();
                return;
            }
            board[x][y] = value;
        }
    };
}

