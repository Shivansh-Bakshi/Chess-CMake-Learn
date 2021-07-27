#include "game.h"
#include <iostream>

using namespace ch::game;

Game::Game()
{
    b = Board();
    b.setup();

    // Initialize current turn to white
    c_currTurn = true;

    // The new Game is active
    c_isActive = true;
    // token check
}

void Game::Move()
{
    std::cout << "Select a piece (example, A 1): ";
    uint8_t x, y;
    std::cin >> y >> x;
    y = y - 'A';
    x = x - '1';

    std::cout << "Selected Piece : " << static_cast<int>(b.getPieceAtIndex(x, y)) << "\n";
}

void Game::Display()
{
    b.display();
}