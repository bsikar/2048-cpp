#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <cmath>
#include "window.h"


Game::MainWindow::MainWindow() : Fl_Window(WIDTH, HEIGHT, "2048") {
    color(BACKGROUND_COLOR);
}

int Game::MainWindow::play() {
    show();
    return Fl::run();
}

int Game::MainWindow::handle(int event) {
    if (event != FL_KEYDOWN) {
        return Fl_Window::handle(event);
    }

    if (Fl::event_key() == FL_Up) {
        logic.moveUp();
        logic.spawnTile();
        redraw();
    } else if (Fl::event_key() == FL_Down) {
        logic.moveDown();
        logic.spawnTile();
        redraw();
    } else if (Fl::event_key() == FL_Left) {
        logic.moveLeft();
        logic.spawnTile();
        redraw();
    } else if (Fl::event_key() == FL_Right) {
        logic.moveRight();
        logic.spawnTile();
        redraw();
    }

    return 1;
}

void Game::MainWindow::draw() {
    Fl_Window::draw();
    logic.printBoard();
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            drawTile(i, j);
            drawGrid();
        }
    }
}

void Game::MainWindow::drawTile(int i, int j) {
    auto boardValue = logic.board[i][j];
    if (boardValue == 0) {
        return;
    }

    // the color of the tile is determined by the log base 2 of the value
    // this is because the value doubles every time you merge
    // so the color should also double
    auto colorIndex = static_cast<int>(log2(boardValue));
    auto color = TILE_COLORS[colorIndex];

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

void Game::MainWindow::drawGrid() {
    fl_color(LINE_COLOR);
    fl_line_style(FL_SOLID, THICKNESS * 2);
    fl_rect(0, 0, WIDTH, HEIGHT);
    fl_line_style(FL_SOLID, THICKNESS);

    for (auto i = 1; i < GRID_ROWS; i++) {
        for (auto j = 1; j < GRID_COLS; j++) {
            fl_line(100 * j, 0, 100 * j, HEIGHT);
            fl_line(0, 100 * i, WIDTH, 100 * i);
        }
    }
}

