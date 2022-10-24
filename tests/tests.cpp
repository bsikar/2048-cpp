#include <gtest/gtest.h>
#include "../src/game/logic.h"

using namespace Game;

TEST(Test1, MoveDown1) {
    Logic logic = Logic();

    logic.board = {{
		{0, 0, 0, 0},
 		{0, 0, 2, 0},
 		{2, 0, 0, 0},
 		{0, 0, 0, 0}
    }};

    logic.moveDown();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{0, 0, 0, 0},
 		{0, 0, 0, 0},
 		{0, 0, 0, 0},
 		{2, 0, 2, 0}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveLeft2) {
    Logic logic = Logic();

    logic.board = {{
		{0, 0, 0, 0},
 		{0, 0, 4, 0},
 		{0, 0, 0, 0},
 		{2, 0, 2, 0}
    }};

    logic.moveLeft();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{0, 0, 0, 0},
 		{4, 0, 0, 0},
 		{0, 0, 0, 0},
 		{4, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveUp3) {
    Logic logic = Logic();

    logic.board = {{
		{0, 0, 0, 0},
 		{4, 0, 0, 0},
 		{2, 0, 0, 0},
 		{4, 0, 0, 0}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{4, 0, 0, 0},
 		{2, 0, 0, 0},
 		{4, 0, 0, 0},
 		{0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveRight4) {
    Logic logic = Logic();

    logic.board = {{
		{4, 0, 2, 0},
 		{2, 0, 0, 0},
 		{4, 0, 0, 0},
 		{0, 0, 0, 0}
    }};

    logic.moveRight();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{0, 0, 4, 2},
 		{0, 0, 0, 2},
 		{0, 0, 0, 4},
 		{0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveRight5) {
    Logic logic = Logic();

    logic.board = {{
		{0, 0, 4, 2},
 		{0, 2, 0, 2},
 		{0, 0, 0, 4},
 		{0, 0, 0, 0}
    }};

    logic.moveRight();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{0, 0, 4, 2},
 		{0, 0, 0, 4},
 		{0, 0, 0, 4},
 		{0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveDown6) {
    Logic logic = Logic();

    logic.board = {{
		{0, 0, 4, 2},
 		{0, 0, 0, 4},
 		{0, 0, 0, 4},
 		{0, 0, 2, 0}
    }};

    logic.moveDown();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{0, 0, 0, 0},
 		{0, 0, 0, 0},
 		{0, 0, 4, 2},
 		{0, 0, 2, 8}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveUp7) {
    Logic logic = Logic();

    logic.board = {{
		{0, 0, 0, 0},
 		{0, 0, 0, 0},
 		{2, 0, 4, 2},
 		{0, 0, 2, 8}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{2, 0, 4, 2},
 		{0, 0, 2, 8},
 		{0, 0, 0, 0},
 		{0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveUp8) {
    Logic logic = Logic();

    logic.board = {{
		{2, 0, 4, 2},
 		{0, 0, 2, 8},
 		{0, 0, 0, 0},
 		{2, 0, 0, 0}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{4, 0, 4, 2},
 		{0, 0, 2, 8},
 		{0, 0, 0, 0},
 		{0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveRight9) {
    Logic logic = Logic();

    logic.board = {{
		{4, 0, 4, 2},
 		{0, 0, 2, 8},
 		{0, 0, 0, 0},
 		{0, 2, 0, 0}
    }};

    logic.moveRight();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{0, 0, 8, 2},
 		{0, 0, 2, 8},
 		{0, 0, 0, 0},
 		{0, 0, 0, 2}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveDown10) {
    Logic logic = Logic();

    logic.board = {{
		{0, 0, 8, 2},
 		{0, 0, 2, 8},
 		{0, 0, 0, 2},
 		{0, 0, 0, 2}
    }};

    logic.moveDown();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{0, 0, 0, 0},
 		{0, 0, 0, 2},
 		{0, 0, 8, 8},
 		{0, 0, 2, 4}
    }};

    ASSERT_EQ(logic.board, board);
}


TEST(Test1, MoveLeft11) {
    Logic logic = Logic();

    logic.board = {{
		{0, 0, 0, 0},
 		{2, 0, 0, 2},
 		{0, 0, 8, 8},
 		{0, 0, 2, 4}
    }};

    logic.moveLeft();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
		{ 0,  0,  0,  0},
 		{ 4,  0,  0,  0},
 		{16,  0,  0,  0},
 		{ 2,  4,  0,  0}
    }};

    ASSERT_EQ(logic.board, board);
}

