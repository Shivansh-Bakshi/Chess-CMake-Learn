#ifndef CH_BOARD_H
#define CH_BOARD_H

#include <stdint.h>
#include <vector>
#include "pieces.h"

static constexpr uint8_t BOARD_DIM = 8;

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
        
        bool isSelectValid(bool currTurn, uint8_t s_x, uint8_t s_y);

        public:

        // Default Constructor
        Board();

        // Setup Board
        void setup();

        // Update Canvas
        // Called when a move is made
        // Parameters:
        // p_i, p_j = row,col index of piece on the board
        // t_x, t_y = translation in x, y of the piece
        void updateCanvas(uint8_t p_i, uint8_t p_j, uint8_t t_x, uint8_t t_y);
        
        // Display Board
        void display();

        int8_t getPieceAtIndex(uint8_t x, uint8_t y);
    };
}

#endif