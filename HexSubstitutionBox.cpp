#include <string>

#include "HexSubstitutionBox.h"

int HexSubstitutionBox::sub(int val)
{
    int row = val >> 4;
    int col = val & 15;
    return lookup[row][col];
}
