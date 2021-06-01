#ifndef CH_PIECES_H
#define CH_PIECES_H

#include <stdint.h>

namespace ch {
    namespace components {

        enum class pieceval : int8_t {
            KING_WHITE = -6, 
            QUEEN_WHITE, 
            ROOK_WHITE, 
            BISHOP_WHITE, 
            KNIGHT_WHITE, 
            PAWN_WHITE,
            DEFAULT,
            PAWN_BLACK, 
            KNIGHT_BLACK, 
            BISHOP_BLACK, 
            ROOK_BLACK, 
            QUEEN_BLACK, 
            KING_BLACK
        };

        class Piece {
            pieceval value;
            public:

            // Defualt Constructor
            Piece();

            // New piece of given value
            Piece(pieceval);

            // Get Piece value as pieceval
            pieceval getValue() const;

            // Get Piece value as integer
            int8_t getIntValue() const;
        };
    }
}

#endif