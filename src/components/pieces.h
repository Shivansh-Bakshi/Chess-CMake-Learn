#ifndef CH_PIECES_H
#define CH_PIECES_H

#include <stdint.h>
#include <string>

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
            KING_BLACK,
            QUEEN_BLACK,
            ROOK_BLACK,
            BISHOP_BLACK,
            KNIGHT_BLACK,
            PAWN_BLACK
        };

        class Piece {
            pieceval value;
            bool moved;
            std::wstring unicodeSymbol;
            public:

            // Defualt Constructor
            Piece();

            // New piece of given value
            Piece(pieceval);

            // Updated moved status to true
            void updateMoved();

            // Get Piece value as pieceval
            pieceval getValue() const;

            // Get Piece value as integer
            int8_t getIntValue() const;

            // Has the piece moved from it's initial position
            bool hasMoved() const;

            // Return the unicode character code corresponding to it
            std::wstring getUnicode() const;
        };
    }
}

#endif