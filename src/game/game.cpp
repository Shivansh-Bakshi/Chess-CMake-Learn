#include "game.h"
#include "../utils/keyutils.h"
#include <iostream>
#include <conio.h>

using namespace ch::game;

void Game::moveHighlight(bool displayPossible)
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

selectSource:
    moveHighlight(false);

    if(b.isSelectValid(c_currTurn, x, y)) {
        std::cout << "Selected Piece : " << static_cast<int>(b.getPieceAtIndex(x, y)) << std::endl;
        uint8_t countPossible = b.getPossibleMoves(x, y);

        if (countPossible == 0) {
            std::cout << "This piece cannot move. Select another piece" << std::endl;
            goto selectSource;
        }
        moveHighlight(true);

        if(b.isValidMove(c_currTurn, x, y)) {
            std::cout << "Valid move" << std::endl;
            
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

void Game::Display()
{
    b.display();
}