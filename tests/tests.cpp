#include <gtest/gtest.h>
#include "../src/game/logic.h"

using namespace Game;

TEST(MoveUp, Test1) {
    Logic logic = Logic();

    logic.board = {{
        {0, 0, 0, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {0, 0, 4, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}

TEST(MoveLeft, Test1) {
    Logic logic = Logic();

    logic.board = {{
        {0, 0, 4, 0},
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 0, 0, 0}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {4, 0, 0, 0},
        {0, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}

TEST(MoveUp, Test2) {
    Logic logic = Logic();

    logic.board = {{
        {4, 0, 0, 0},
        {2, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {4, 0, 0, 0},
        {4, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}

TEST(MoveUp, Test3) {
    Logic logic = Logic();

    logic.board = {{
        {4, 0, 0, 0},
        {4, 0, 0, 0},
        {0, 0, 0, 0},
        {2, 0, 0, 0}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {8, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}

TEST(MoveLeft, Test2) {
    Logic logic = Logic();

    logic.board = {{
        {8, 0, 2, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {8, 2, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}

TEST(MoveDown, Test1) {
    Logic logic = Logic();

    logic.board = {{
        {8, 2, 2, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {8, 0, 0, 0},
        {2, 2, 2, 0}
    }};

    ASSERT_EQ(logic.board, board);
}

TEST(MoveRight, Test1) {
    Logic logic = Logic();

    logic.board = {{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {8, 0, 0, 0},
        {2, 2, 2, 2}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 8},
        {0, 0, 4, 4}
    }};

    ASSERT_EQ(logic.board, board);
}

TEST(MoveRight, Test2) {
    Logic logic = Logic();

    logic.board = {{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 8},
        {2, 0, 4, 4}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 8},
        {0, 0, 2, 8}
    }};

    ASSERT_EQ(logic.board, board);
}

TEST(MoveUp, Test4) {
    Logic logic = Logic();

    logic.board = {{
        {0, 0, 0, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 8},
        {0, 0, 2, 8}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {0, 0, 4, 16},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}

TEST(MoveRight, Test3) {
    Logic logic = Logic();

    logic.board = {{
        {0, 0, 4, 16},
        {0, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    logic.moveUp();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
        {0, 0, 4, 16},
        {0, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 0, 0, 0}
    }};

    ASSERT_EQ(logic.board, board);
}
