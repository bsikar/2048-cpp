#pragma once
#include <array>
#include <FL/Fl_Window.H>
#include "logic.h"

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
        Logic logic = Logic();
        int handle(int event) override;
        void draw() override;
        void drawGrid();
        void drawTile(int, int);
    };
}

