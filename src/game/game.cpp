#include "game.h"
#include "../utils/keyutils.h"
#include <iostream>
#include <conio.h>

using namespace ch::game;

Game::Game()
{
    b = Board();
    b.setup();

    // Initialize current turn to white
    c_currTurn = true;

    // The new Game is active
    c_isActive = true;
}

void Game::Move()
{
    std::cout << "Select a piece" << std::endl;
    int inp = 0;
    uint8_t x, y;
    x = 0;
    y = 0;

takeInput:
    b.display(x, y);
    inp = getch();
    // Key pressed was a special key
    if (inp == 224) {
        switch(inp = getch()) {
            case KEY_UP : {
                std::cout << "Up" << std::endl;
                if (x == 0) {
                    x = 7;
                } else {
                    x--;
                }
                break;
            }
            case KEY_DOWN : {
                std::cout << "Down" << std::endl;
                if (x == 7) {
                    x = 0;
                } else {
                    x++;
                }
                break;
            }
            case KEY_LEFT : {
                std::cout << "Left" << std::endl;
                if (y == 0) {
                    y = 7;
                } else {
                    y--;
                }
                break;
            }
            case KEY_RIGHT : {
                std::cout << "Right" << std::endl;
                if (y == 7) {
                    y = 0;
                } else {
                    y++;
                }
                break;
            }
        }
    } else {
        goto selectionDone;
    }

    goto takeInput;

selectionDone:
    std::cout << "Selected Piece : " << static_cast<int>(b.getPieceAtIndex(x, y)) << "\n";
}

void Game::Display()
{
    b.display();
}