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