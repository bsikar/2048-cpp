#include <gtest/gtest.h>
#include "../src/game/game.h"

using namespace Game;

TEST(GameTest, Test1) {
    Logic logic = Logic();

    logic.printBoard();

    ASSERT_EQ(1, 1);
}

