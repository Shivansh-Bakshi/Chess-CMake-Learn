#include "game.h"
#include "../utils/keyutils.h"
#include <iostream>
#include <conio.h>

using namespace ch::game;

void Game::moveHighlight()
{
    uint8_t inp = 0;
takeInput:
    b.display(x, y);
    inp = getch();
    // Key pressed was a special key
    if (inp == 224) {
        switch(inp = getch()) {
            case KEY_UP : {
                if (x == 0) {
                    x = 7;
                } else {
                    x--;
                }
                break;
            }
            case KEY_DOWN : {
                if (x == 7) {
                    x = 0;
                } else {
                    x++;
                }
                break;
            }
            case KEY_LEFT : {
                if (y == 0) {
                    y = 7;
                } else {
                    y--;
                }
                break;
            }
            case KEY_RIGHT : {
                if (y == 7) {
                    y = 0;
                } else {
                    y++;
                }
                break;
            }
        }
    } else {
        goto moveHighlightDone;
    }
    goto takeInput;

moveHighlightDone:
    return;
}

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
    if (c_currTurn) {
        std::cout << "White's Turn!" << std::endl;
    } else {
        std::cout << "Black's Turn!" << std::endl;
    }
    std::cout << "Select a piece" << std::endl;
    x = 0;
    y = 0;

makeSelection:
    moveHighlight();

    if(b.isSelectValid(c_currTurn, x, y)) {
        std::cout << "Selected Piece : " << static_cast<int>(b.getPieceAtIndex(x, y)) << std::endl;
        b.getPossibleMoves(x, y);

        uint8_t s_x = x;
        uint8_t s_y = y;

        b.displayPossibleMoves(s_x, s_y);
    } else {
        std::cout << "Invalid Selection. Please choose from one of your pieces" << std::endl;
        goto makeSelection;
    }
}

void Game::Display()
{
    b.display();
}