#include "pieces.h"
#include "../utils/typeutils.h"

using namespace ch::components;
using namespace ch::utils;

Piece::Piece()
{
    // Default Constructor. Initialize value to 0
    this->value = pieceval::DEFAULT;
    this->moved = false;
}

Piece::Piece(pieceval value)
{
    // Parameterized Constructor. Set this pieces value to value
    this->value = value;
    this->moved = false;
    switch(value) {
        case pieceval::KING_WHITE : {
            this->unicodeSymbol = L"\u2654";
            break;
        }
        case pieceval::QUEEN_WHITE : {
            this->unicodeSymbol = L"\u2655";
            break;
        }
        case pieceval::ROOK_WHITE : {
            this->unicodeSymbol = L"\u2656";
            break;
        }
        case pieceval::BISHOP_WHITE : {
            this->unicodeSymbol = L"\u2657";
            break;
        }
        case pieceval::KNIGHT_WHITE : {
            this->unicodeSymbol = L"\u2658";
            break;
        }
        case pieceval::PAWN_WHITE : {
            this->unicodeSymbol = L"\u2659";
            break;
        }
        case pieceval::KING_BLACK : {
            this->unicodeSymbol = L"\u265A";
            break;
        }
        case pieceval::QUEEN_BLACK : {
            this->unicodeSymbol = L"\u265B";
            break;
        }
        case pieceval::ROOK_BLACK : {
            this->unicodeSymbol = L"\u265C";
            break;
        }
        case pieceval::BISHOP_BLACK : {
            this->unicodeSymbol = L"\u265D";
            break;
        }
        case pieceval::KNIGHT_BLACK : {
            this->unicodeSymbol = L"\u265E";
            break;
        }
        case pieceval::PAWN_BLACK : {
            this->unicodeSymbol = L"\u265F";
            break;
        }
    }
}

void Piece::updateMoved()
{
    this->moved = true;
}

pieceval Piece::getValue() const
{
    return this->value;
}

int8_t Piece::getIntValue() const
{
    return as_int8(this->value);
}

bool Piece::hasMoved() const
{
    return this->moved;
}

std::wstring Piece::getUnicode() const
{
    return this->unicodeSymbol;
}