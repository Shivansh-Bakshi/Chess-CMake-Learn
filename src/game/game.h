#ifndef CH_GAME_H
#define CH_GAME_H

#include "../components/board.h"

using namespace ch::components;

namespace ch {
    namespace game {
        class Game {
            Board b;

            // true  = white's turn
            // false = black's turn
            bool c_currTurn;

            // true  = Game has not ended
            // false = Game has ended
            bool c_isActive;

            public:

            // Default Constructor
            Game();

            // Make a move
            void Move();

            // Display the board
            void Display();
        };
    }
}

#endif