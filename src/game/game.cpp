#include "game.h"
#include "../utils/keyutils.h"
#include <iostream>
#include <conio.h>

using namespace ch::game;

uint8_t Game::moveHighlight(bool displayPossible)
{
    uint8_t inp = 0;
takeInput:
    if(displayPossible) {
        b.displayPossibleMoves(x, y);
    } else {
        b.display(x, y);
    }
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
    return inp;
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
    uint8_t inp;

selectSource:
    inp = moveHighlight(false);
    // If q was pressed. End game immediately
    if (inp == 113) {
        std::cout << "Qutting Game" << std::endl;
        c_isActive = false;
        return;
    }

    if(b.isSelectValid(c_currTurn, x, y)) {
        uint8_t countPossible = b.getPossibleMoves(x, y);

        if (countPossible == 0) {
            std::cout << "This piece cannot move. Select another piece" << std::endl;
            goto selectSource;
        }
        uint8_t s_x = x;
        uint8_t s_y = y;
        moveHighlight(true);

        if(b.isValidMove(c_currTurn, x, y)) {
            std::cout << "Valid move" << std::endl;
            b.updateCanvas(c_currTurn, s_x, s_y, x, y);
            c_currTurn = !c_currTurn;
            return;
        } else {
            std::cout << "Invalid Destination" << std::endl << "Select a piece" << std::endl;
            goto selectSource;
        }

    } else {
        std::cout << "Invalid Selection. Please choose from one of your pieces" << std::endl;
        goto selectSource;
    }
}

void Game::Display() const
{
    b.display();
}

bool Game::isGameActive() const
{
    return c_isActive;
}