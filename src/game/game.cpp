#include "game.h"

Game::MainWindow::MainWindow() : Fl_Window(WIDTH, HEIGHT, "2048") {
    color(BACKGROUND_COLOR);
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

int Game::MainWindow::play() {
    show();
    return Fl::run();
}

int Game::MainWindow::handle(int event) {
    switch (event) {
        case FL_KEYDOWN:
            switch (Fl::event_key()) {
                case FL_Up:
                    moveUp();
                    break;
                case FL_Down:
                    moveDown();
                    break;
                case FL_Left:
                    moveLeft();
                    break;
                case FL_Right:
                    moveRight();
                    break;
            }
            return 1;
        default:
            return Fl_Window::handle(event);
    }
}

void Game::MainWindow::moveUp() {
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

    spawnTile();
    redraw();
}

void Game::MainWindow::moveDown() {
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

    spawnTile();
    redraw();
}

void Game::MainWindow::moveLeft() {
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

    spawnTile();
    redraw();
}

void Game::MainWindow::moveRight() {
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

    spawnTile();
    redraw();
}

void Game::MainWindow::spawnTile() {
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

void Game::MainWindow::draw() {
    Fl_Window::draw();
    printBoard();
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            drawTile(i, j);
            drawGrid();
        }
    }
}

void Game::MainWindow::drawTile(int i, int j) {
    auto boardValue = board[i][j];
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

void Game::MainWindow::printBoard() {
    for (auto i = 0; i < GRID_ROWS; i++) {
        for (auto j = 0; j < GRID_COLS; j++) {
            std::cout << std::setw(4) << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

