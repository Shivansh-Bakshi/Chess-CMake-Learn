#include <iostream>
#include "../game/game.h"
#include "../utils/typeutils.h"

using namespace ch::components;
using namespace ch::utils;
using namespace ch::game;

int main()
{
    Game g;
    g.Display();

    g.Move();
}