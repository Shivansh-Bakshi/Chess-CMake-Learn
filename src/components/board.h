#ifndef CH_BOARD_H
#define CH_BOARD_H

#include <stdint.h>
#include <vector>
#include "pieces.h"
#include "../utils/wincolorutils.h"

#define BOARD_DIM  (8)
#define SELECTED_COLOR (14)

using namespace ch::utils;

namespace ch::components {
    
    // Member objects:
    // matrix : 8 x 8 matrix of pieces
    // active_white : vector of (row,col) pairs where white pieces are placed
    // active_black : vector of (row,col) pairs where black pieces are placed
    //
    // We use a vector to store pairs to avoid having to search the entire board everytime for making a move
    class Board {

        Piece matrix[BOARD_DIM][BOARD_DIM];
        std::vector<std::pair<uint8_t, uint8_t>> active_white;
        std::vector<std::pair<uint8_t, uint8_t>> active_black;
        std::vector<std::pair<uint8_t, uint8_t>> allowed_moves;
        WinColorUtils c;
        
        // Returns if a position on the matrix is empty or not
        bool isEmptySpace(int8_t p_x, int8_t p_y) const;

        // Returns true if the position is withing board boundaries
        bool isInBoardBounds(int8_t p_x, int8_t p_y) const;

        public:

        // Default Constructor
        Board();

        // Setup Board
        void setup();

        // Update Canvas
        // Called when a move is made
        // Parameters:
        // s_x, s_y = x,y index of source of piece on the board
        // d_x, d_y = destination in x, y of the piece
        void updateCanvas(uint8_t s_x, uint8_t s_y, uint8_t d_x, uint8_t d_y);
        
        // Display Board
        void display() const;
        
        // Display Selected Piece
        void display(uint8_t p_i, uint8_t p_j) const;

        // Returns the value of the piece at a given position on the board
        int8_t getPieceAtIndex(uint8_t x, uint8_t y) const;

        // Returns if the selected piece is a valid piece or not, depending on the turn.
        bool isSelectValid(bool currTurn, uint8_t s_x, uint8_t s_y) const;

        // Get the possible moves a selected piece can make
        uint8_t getPossibleMoves(uint8_t s_x, uint8_t s_y);

        // Display the possible moves after getting them.
        void displayPossibleMoves(uint8_t s_x, uint8_t s_y) const;

        bool isValidMove(bool currTurn, uint8_t d_x, uint8_t d_y) const;
    };
}

#endif