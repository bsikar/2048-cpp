// this is my attempt at a simple 2048 game

#include <Fl/Fl.H>
#include "game/game.h"

int main(void) {
    Game::MainWindow window;
    window.show();

    return Fl::run();
}
