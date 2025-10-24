#include "Game.h"
#include "Config.h"

int main() {

   Game sandGame {"Falling Sand Simulation", WINDOW_WIDTH, WINDOW_HEIGHT};

   sandGame.run();
}