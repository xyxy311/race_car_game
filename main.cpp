#include "game.h"
#include "support.h"
#include "map.h"
#include "car.h"

int main() {
    Game game;
    game.gameInit();
    game.run();
    game.close();
}