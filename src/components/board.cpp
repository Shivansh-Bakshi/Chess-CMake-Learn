#include "board.h"
#include "../utils/typeutils.h"
#include <algorithm>
#include <cstdio>
#include <fcntl.h>
#include <io.h>

using namespace ch::components;
using namespace ch::utils;

bool Board::isEmptySpace(int8_t p_x, int8_t p_y) const
{
    if (matrix[p_x][p_y].getValue() == pieceval::DEFAULT) {
        return true;
    }
    return false;
}

bool Board::isInBoardBounds(int8_t p_x, int8_t p_y) const
{
    if (p_x >= BOARD_DIM || p_x < 0 || p_y >= BOARD_DIM || p_y < 0) {
        return false;
    }
    return true;
}

bool Board::isOpposingPiecePresent(int8_t p, int8_t p_x, int8_t p_y) const
{
    int8_t d_p = matrix[p_x][p_y].getIntValue();
    if ((p ^ d_p) < 0 && (p & d_p) != 0) {
        return true;
    }
    return false;
}

Board::Board()
{
    c = WinColorUtils();
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
        active_black.push_back(std::make_pair(BOARD_DIM - 2, i));
    }

    // Rest of the pieces
    matrix[BOARD_DIM - 1][0] = matrix[BOARD_DIM - 1][BOARD_DIM - 1] = Piece(pieceval::ROOK_BLACK);
    active_black.push_back(std::make_pair(BOARD_DIM - 1, 0));
    active_black.push_back(std::make_pair(BOARD_DIM - 1, BOARD_DIM - 1));

    matrix[BOARD_DIM - 1][1] = matrix[BOARD_DIM - 1][BOARD_DIM - 2] = Piece(pieceval::KNIGHT_BLACK);
    active_black.push_back(std::make_pair(BOARD_DIM - 1, 1));
    active_black.push_back(std::make_pair(BOARD_DIM - 1, BOARD_DIM - 2));
    
    matrix[BOARD_DIM - 1][2] = matrix[BOARD_DIM - 1][BOARD_DIM - 3] = Piece(pieceval::BISHOP_BLACK);
    active_black.push_back(std::make_pair(BOARD_DIM - 1, 2));
    active_black.push_back(std::make_pair(BOARD_DIM - 1, BOARD_DIM - 3));
    
    matrix[BOARD_DIM - 1][3] = Piece(pieceval::QUEEN_BLACK);
    active_black.push_back(std::make_pair(BOARD_DIM - 1, 3));
    
    matrix[BOARD_DIM - 1][4] = Piece(pieceval::KING_BLACK);
    active_black.push_back(std::make_pair(BOARD_DIM - 1, 4));

}

void Board::updateCanvas(bool currTurn, uint8_t s_x, uint8_t s_y, uint8_t d_x, uint8_t d_y)
{
    Piece temp = matrix[s_x][s_y];
    matrix[s_x][s_y] = Piece(pieceval::DEFAULT);
    // Remove old location from active list
    if (currTurn) {
       std::vector<std::pair<uint8_t, uint8_t>>::iterator pos = std::find(active_white.begin(), active_white.end(), std::make_pair(s_x, s_y));
       if (pos != active_white.end()) {
           active_white.erase(pos);
       } 
    } else {
       std::vector<std::pair<uint8_t, uint8_t>>::iterator pos = std::find(active_black.begin(), active_black.end(), std::make_pair(s_x, s_y));
       if (pos != active_black.end()) {
           active_black.erase(pos);
       } 
    }
    // if destination has an opposing piece which is being taken, remove it from active list of opposite side
    if (isOpposingPiecePresent(temp.getIntValue(), d_x, d_y)) {
        if (currTurn) {
            std::vector<std::pair<uint8_t, uint8_t>>::iterator pos = std::find(active_black.begin(), active_black.end(), std::make_pair(d_x, d_y));
            if (pos != active_black.end()) {
                active_black.erase(pos);
            }
        } else {
            std::vector<std::pair<uint8_t, uint8_t>>::iterator pos = std::find(active_white.begin(), active_white.end(), std::make_pair(d_x, d_y));
            if (pos != active_white.end()) {
                active_white.erase(pos);
            } 
        }
    }
    matrix[d_x][d_y] = temp;
    // set hasMoved to true if it hasn't
    if (!matrix[d_x][d_y].hasMoved()) {
        matrix[d_x][d_y].updateMoved();
    }
    // Insert new position in active list
    if (currTurn) {
        active_white.push_back(std::make_pair(d_x, d_y));
    } else {
        active_black.push_back(std::make_pair(d_x, d_y));
    }
}


void Board::display() const
{
    for(uint8_t i = 0; i < BOARD_DIM; i++) {
        std::cout << " \t" << (char)('A' + i);
    }
    std::cout << std::endl;
    for (uint8_t i = 0; i < BOARD_DIM; i++) {
        std::cout << i + 1 << "\t";
        for (uint8_t j = 0; j < BOARD_DIM; j++) {
            // std::cout << static_cast<int>(matrix[i][j].getIntValue()) << "\t";
            if ((i + j) % 2 == 0) {
                c.setBackgroundLight();
            }
            _setmode(_fileno(stdout), _O_WTEXT);
            std::wcout << matrix[i][j].getUnicode() << "\t";
            c.resetColor();
        }
        _setmode(_fileno(stdout), O_TEXT);
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

void Board::display(uint8_t p_i, uint8_t p_j) const
{
    for(uint8_t i = 0; i < BOARD_DIM; i++) {
        std::cout << " \t" << (char)('A' + i);
    }
    std::cout << std::endl;
    for (uint8_t i = 0; i < BOARD_DIM; i++) {
        std::cout << i + 1 << "\t";
        for (uint8_t j = 0; j < BOARD_DIM; j++) {
            if (i == p_i && j == p_j) {
                c.setSelectedColor();
                _setmode(_fileno(stdout), _O_WTEXT);
                std::wcout << matrix[i][j].getUnicode() << "\t";
                c.resetColor();
                continue;
            } else if ((i + j) % 2 == 0) {
                c.setBackgroundLight();
            }
            _setmode(_fileno(stdout), _O_WTEXT);
            std::wcout << matrix[i][j].getUnicode() << "\t";
            c.resetColor();
        }
        _setmode(_fileno(stdout), O_TEXT);
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

int8_t Board::getPieceAtIndex(uint8_t x, uint8_t y) const
{
    return matrix[x][y].getIntValue();
}

bool Board::isSelectValid(bool currTurn, uint8_t s_x, uint8_t s_y) const
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

uint8_t Board::getPossibleMoves(uint8_t s_x, uint8_t s_y)
{
    uint8_t countMoves = 0;
    allowed_moves.clear();
    Piece p = matrix[s_x][s_y];
    pieceval p_val = p.getValue();
    // If selected piece is a black pawn
    if (p_val == pieceval::PAWN_BLACK) {
        if (!p.hasMoved()) {
            // If the black pawn has not moved, it can move 2 spaces up if those 2 spaces are empty
            if (isEmptySpace(s_x - 1, s_y) && isInBoardBounds(s_x - 1, s_y)) {
                allowed_moves.push_back(std::make_pair(s_x - 1, s_y));
                countMoves++;
                if (isEmptySpace(s_x - 2, s_y) && isInBoardBounds(s_x - 2, s_y)) {
                    allowed_moves.push_back(std::make_pair(s_x - 2, s_y));
                    countMoves++;
                }
            }
        } else {
            // If the black pawn has moved before, it can only move 1 space up
            if (isEmptySpace(s_x - 1, s_y) && isInBoardBounds(s_x - 1, s_y)) {
            allowed_moves.push_back(std::make_pair(s_x - 1, s_y));
            countMoves++;
            }  
        }
        // If an opposing piece is on the immediate front diagonals, it can take it
        if (isOpposingPiecePresent(p.getIntValue(), s_x - 1, s_y - 1)) {
            allowed_moves.push_back(std::make_pair(s_x - 1, s_y - 1));
            countMoves++;
        }
        if (isOpposingPiecePresent(p.getIntValue(), s_x - 1, s_y + 1)) {
            allowed_moves.push_back(std::make_pair(s_x - 1, s_y + 1));
            countMoves++;
        }
    }
    // If the selected piece is a white pawn
    else if (p_val == pieceval::PAWN_WHITE) {
            if (!p.hasMoved()) {
            // If the white pawn has not moved, it can move 2 spaces down if those 2 spaces are empty
            if (isEmptySpace(s_x + 1, s_y) && isInBoardBounds(s_x + 1, s_y)) {
                allowed_moves.push_back(std::make_pair(s_x + 1, s_y));
                countMoves++;
                if (isEmptySpace(s_x + 2, s_y) && isInBoardBounds(s_x + 2, s_y)) {
                    allowed_moves.push_back(std::make_pair(s_x + 2, s_y));
                    countMoves++;
                }
            }
        } else {
            // If the white pawn has moved before, it can only move 1 space down
            if (isEmptySpace(s_x + 1, s_y) && isInBoardBounds(s_x + 1, s_y)) {
                allowed_moves.push_back(std::make_pair(s_x + 1, s_y));
                countMoves++;
            }  
        }
        // If an opposing piece is on the immediate below diagonals, it can take it
        if (isOpposingPiecePresent(p.getIntValue(), s_x + 1, s_y - 1)) {
            allowed_moves.push_back(std::make_pair(s_x + 1, s_y - 1));
            countMoves++;
        }
        if (isOpposingPiecePresent(p.getIntValue(), s_x + 1, s_y + 1)) {
            allowed_moves.push_back(std::make_pair(s_x + 1, s_y + 1));
            countMoves++;
        }
    }
    // If the selected piece is a rook
    else if (p_val == pieceval::ROOK_BLACK || p_val == pieceval::ROOK_WHITE) {
        // Rook can move top, bottom, right, left
        int8_t m_x[4] = {0, 0, 1, -1};
        int8_t m_y[4] = {1, -1, 0, 0};

        uint8_t x_off = 0;
        uint8_t y_off = 0;

        // Outer for loop for each direction
        for (uint8_t i = 0; i < 4; i++) {
            x_off = m_x[i];
            y_off = m_y[i];
            // Inner loop to move in direction from selected position till board boundary or another piece is hit
            while ((isEmptySpace(s_x + x_off, s_y + y_off) || 
                    isOpposingPiecePresent(p.getIntValue(), s_x + x_off, s_y + y_off)) && 
                    isInBoardBounds(s_x + x_off, s_y + y_off)) {
                allowed_moves.push_back(std::make_pair(s_x + x_off, s_y + y_off));
                countMoves++;
                if (isOpposingPiecePresent(p.getIntValue(), s_x + x_off, s_y + y_off)) {
                    break;
                }
                x_off += m_x[i];
                y_off += m_y[i];
            }
        }
    }
    // If the selected piece is a bishop
    else if (p_val == pieceval::BISHOP_BLACK || p_val == pieceval::BISHOP_WHITE) {
        // Bishop can move top left, top right, bottom left, bottom right digonals
        int8_t m_x[4] = {-1, 1, 1, -1};
        int8_t m_y[4] = {1, -1, 1, -1};

        uint8_t x_off = 0;
        uint8_t y_off = 0;

        // Outer for loop for each direction
        for (uint8_t i = 0; i < 4; i++) {
            x_off = m_x[i];
            y_off = m_y[i];
            // Inner loop to move in direction from selected position till board boundary or another piece is hit
            while ((isEmptySpace(s_x + x_off, s_y + y_off) || 
                    isOpposingPiecePresent(p.getIntValue(), s_x + x_off, s_y + y_off)) && 
                    isInBoardBounds(s_x + x_off, s_y + y_off)) {
                allowed_moves.push_back(std::make_pair(s_x + x_off, s_y + y_off));
                countMoves++;
                if (isOpposingPiecePresent(p.getIntValue(), s_x + x_off, s_y + y_off)) {
                    break;
                }
                x_off += m_x[i];
                y_off += m_y[i];
            }
        }
    }
    // If the selected piece is a knight
    else if (p_val == pieceval::KNIGHT_BLACK || p_val == pieceval::KNIGHT_WHITE) {
        // Knight can only move to 8 possible other squares.
        int8_t m_x[8] = {-2, -2, 2, 2, -1, -1, 1, 1};
        int8_t m_y[8] = {1, -1, 1, -1, -2, 2, -2, 2};
        
        // Only one loop to go through each move
        for (uint8_t i = 0; i < 8; i++) {
            if ((isEmptySpace(s_x + m_x[i], s_y + m_y[i]) || 
                isOpposingPiecePresent(p.getIntValue(), s_x + m_x[i], s_y + m_y[i])) && 
                isInBoardBounds(s_x + m_x[i], s_y + m_y[i])) {
                allowed_moves.push_back(std::make_pair(s_x + m_x[i], s_y + m_y[i]));
                countMoves++;
            }
        }
    }
    // If the selected piece is a queen
    else if (p_val == pieceval::QUEEN_BLACK || p_val == pieceval::QUEEN_WHITE) {
        // Queen can move in directions of both, rook and bishop
        int8_t m_x[8] = {0, 0, 1, -1, -1, 1, 1, -1};
        int8_t m_y[8] = {1, -1, 0, 0, 1, -1, 1, -1};

        uint8_t x_off = 0;
        uint8_t y_off = 0;

        // Outer for loop for each direction
        for (uint8_t i = 0; i < 8; i++) {
            x_off = m_x[i];
            y_off = m_y[i];
            // Inner loop to move in direction from selected position till board boundary or another piece is hit
            while ((isEmptySpace(s_x + x_off, s_y + y_off) || 
                    isOpposingPiecePresent(p.getIntValue(), s_x + x_off, s_y + y_off)) && 
                    isInBoardBounds(s_x + x_off, s_y + y_off)) {
                allowed_moves.push_back(std::make_pair(s_x + x_off, s_y + y_off));
                countMoves++;
                if (isOpposingPiecePresent(p.getIntValue(), s_x + x_off, s_y + y_off)) {
                    break;
                }
                x_off += m_x[i];
                y_off += m_y[i];
            }
        }
    }
    // If the selected piece is a king
    else if (p_val == pieceval::KING_BLACK || p_val == pieceval::KING_WHITE) {
        // King can move once in all 8 directions
        int8_t m_x[8] = {0, 0, 1, -1, -1, 1, 1, -1};
        int8_t m_y[8] = {1, -1, 0, 0, 1, -1, 1, -1};

        // Only one loop to go through each move
        for (uint8_t i = 0; i < 8; i++) {
            if ((isEmptySpace(s_x + m_x[i], s_y + m_y[i]) || 
                isOpposingPiecePresent(p.getIntValue(), s_x + m_x[i], s_y + m_y[i])) && 
                isInBoardBounds(s_x + m_x[i], s_y + m_y[i])) {
                allowed_moves.push_back(std::make_pair(s_x + m_x[i], s_y + m_y[i]));
                countMoves++;
            }
        }
    }

    return countMoves;
}

void Board::displayPossibleMoves(uint8_t s_x, uint8_t s_y) const
{
    for(uint8_t i = 0; i < BOARD_DIM; i++) {
        std::cout << " \t" << (char)('A' + i);
    }
    std::cout << std::endl;
    for (uint8_t i = 0; i < BOARD_DIM; i++) {
        std::cout << i + 1 << "\t";
        for (uint8_t j = 0; j < BOARD_DIM; j++) {
            // If (i, j) is currently highlighted
            if (i == s_x && j == s_y) {
                c.setSelectedColor();
                _setmode(_fileno(stdout), _O_WTEXT);
                std::wcout << matrix[i][j].getUnicode() << "\t";
                c.resetColor();
                continue;
            }
            // If (i, j) is an allowed move:
            else if (std::find(allowed_moves.begin(), allowed_moves.end(), std::make_pair(i, j)) != allowed_moves.end()) {
                c.setPossibleColor();
                _setmode(_fileno(stdout), _O_WTEXT);
                std::wcout << matrix[i][j].getUnicode() << "\t";
                c.resetColor();
                continue;
            }
            else if ((i + j) % 2 == 0){
                c.setBackgroundLight();
            }
            _setmode(_fileno(stdout), _O_WTEXT);
            std::wcout << matrix[i][j].getUnicode() << "\t";
            c.resetColor();
        }
        _setmode(_fileno(stdout), O_TEXT);
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

bool Board::isValidMove(bool currTurn, uint8_t d_x, uint8_t d_y) const
{
    if (std::find(allowed_moves.begin(), allowed_moves.end(), std::make_pair(d_x, d_y)) != allowed_moves.end()) {
        return true;
    }
    return false;
}