#include "pieces.h"
#include "../utils/typeutils.h"

using namespace ch::components;
using namespace ch::utils;

Piece::Piece()
{
    // Default Constructor. Initialize value to 0
    this->value = pieceval::DEFAULT;
}

Piece::Piece(pieceval value)
{
    // Parameterized Constructor. Set this pieces value to value
    this->value = value;
}

pieceval Piece::getValue() const
{
    return this->value;
}

int8_t Piece::getIntValue() const
{
    return as_int8(this->value);
}