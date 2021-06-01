#include "board.h"
#include "../utils/typeutils.h"
#include <algorithm>

using namespace ch::components;
using namespace ch::utils;

Board::Board()
{
    for (int i = 0; i < BOARD_DIM; i++) {
        for (int j = 0 ; j < BOARD_DIM; j++) {
            matrix[i][j] = Piece(pieceval::DEFAULT);
        }
    }
}

void Board::setup()
{
    // Setup white pieces
    // Pawns
    for(uint8_t i = 0; i < BOARD_DIM; i++) {
        matrix[1][i] = Piece(pieceval::PAWN_WHITE);
        active_white.push_back(std::make_pair(1, i));
    }

    // Rest of the pieces
    matrix[0][0] = matrix[0][BOARD_DIM - 1] = Piece(pieceval::ROOK_WHITE);
    active_white.push_back(std::make_pair(0, 0));
    active_white.push_back(std::make_pair(0, BOARD_DIM - 1));
    
    matrix[0][1] = matrix[0][BOARD_DIM - 2] = Piece(pieceval::KNIGHT_WHITE);
    active_white.push_back(std::make_pair(0, 1));
    active_white.push_back(std::make_pair(0, BOARD_DIM - 2));
    
    matrix[0][2] = matrix[0][BOARD_DIM - 3] = Piece(pieceval::BISHOP_WHITE);
    active_white.push_back(std::make_pair(0, 2));
    active_white.push_back(std::make_pair(0, BOARD_DIM - 3));

    matrix[0][3] = Piece(pieceval::QUEEN_WHITE);
    active_white.push_back(std::make_pair(0, 3));
    
    matrix[0][4] = Piece(pieceval::KING_WHITE);
    active_white.push_back(std::make_pair(0, 4));

    // Setup black pieces
    // Pawns
    for(uint8_t i = 0; i < BOARD_DIM; i++) {
        matrix[BOARD_DIM - 2][i] = Piece(pieceval::PAWN_BLACK);
        active_white.push_back(std::make_pair(BOARD_DIM - 2, i));
    }

    // Rest of the pieces
    matrix[BOARD_DIM - 1][0] = matrix[BOARD_DIM - 1][BOARD_DIM - 1] = Piece(pieceval::ROOK_BLACK);
    active_white.push_back(std::make_pair(BOARD_DIM - 1, 0));
    active_white.push_back(std::make_pair(BOARD_DIM - 1, BOARD_DIM - 1));

    matrix[BOARD_DIM - 1][1] = matrix[BOARD_DIM - 1][BOARD_DIM - 2] = Piece(pieceval::KNIGHT_BLACK);
    active_white.push_back(std::make_pair(BOARD_DIM - 1, 1));
    active_white.push_back(std::make_pair(BOARD_DIM - 1, BOARD_DIM - 2));
    
    matrix[BOARD_DIM - 1][2] = matrix[BOARD_DIM - 1][BOARD_DIM - 3] = Piece(pieceval::BISHOP_BLACK);
    active_white.push_back(std::make_pair(BOARD_DIM - 1, 2));
    active_white.push_back(std::make_pair(BOARD_DIM - 1, BOARD_DIM - 3));
    
    matrix[BOARD_DIM - 1][3] = Piece(pieceval::QUEEN_BLACK);
    active_white.push_back(std::make_pair(BOARD_DIM - 1, 3));
    
    matrix[BOARD_DIM - 1][4] = Piece(pieceval::KING_BLACK);
    active_white.push_back(std::make_pair(BOARD_DIM - 1, 4));

}

bool Board::isSelectValid(bool currTurn, uint8_t s_x, uint8_t s_y)
{
    if (currTurn) {
        // If selected piece is an active white piece, return true
        if(std::find(active_white.begin(), active_white.end(), std::make_pair(s_x, s_y)) != active_white.end()) {
            return true;
        } else {
            return false;
        }
    } else {
        // If selected piece is an active black piece, return true
        if(std::find(active_black.begin(), active_black.end(), std::make_pair(s_x, s_y)) != active_black.end()) {
            return true;
        } else {
            return false;
        }
    }
}

void Board::updateCanvas(uint8_t p_i, uint8_t p_j, uint8_t t_x, uint8_t t_y)
{
    Piece temp = matrix[p_i][p_j];
    matrix[p_i][p_j] = Piece(pieceval::DEFAULT);
    matrix[p_i + t_x][p_j + t_y] = temp;
}


void Board::display()
{
    for(uint8_t i = 0; i < BOARD_DIM; i++) {
        std::cout << " \t" << (char)('A' + i);
    }
    std::cout << std::endl;
    for (uint8_t i = 0; i < BOARD_DIM; i++) {
        std::cout << i + 1 << "\t";
        for (uint8_t j = 0; j < BOARD_DIM; j++) {
            std::cout << static_cast<int>(matrix[i][j].getIntValue()) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

int8_t Board::getPieceAtIndex(uint8_t x, uint8_t y)
{
    return matrix[x][y].getIntValue();
}
