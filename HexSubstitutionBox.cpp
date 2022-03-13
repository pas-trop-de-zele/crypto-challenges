#include <string>

#include "HexSubstitutionBox.h"

uint8_t HexSubstitutionBox::sub(uint8_t val)
{
    int row = val >> 4;
    int col = val & 15;
    return lookup[row][col];
}

uint8_t HexSubstitutionBox::sub_inverse(uint8_t val)
{
    int row = val >> 4;
    int col = val & 15;
    return lookup_inverse[row][col];
}
