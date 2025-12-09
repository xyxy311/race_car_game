#include "game.h"

int main() {
    while (1) {
        Game game;
        game.gameInit();
        game.run();
        game.close();
    }
}