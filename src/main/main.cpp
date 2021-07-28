#include <iostream>
#include "../game/game.h"

using namespace ch::components;
using namespace ch::utils;
using namespace ch::game;

int main()
{
    Game g;
    while (g.isGameActive()) {
        g.Move();
    }
    return 0;
}