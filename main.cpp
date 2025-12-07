#include "game.h"
#include "support.h"
#include "map.h"
#include "car.h"

int main() {
    while (1) {
        Game game;
        game.gameInit();
        game.run();
        game.close();
    }
}