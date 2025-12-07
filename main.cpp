#include "game.h"
#include "support.h"
#include "map.h"
#include "car.h"

int main() {
    Game game;
    while (1) {
        game.gameInit();
        game.run();
        game.close();
    }
}