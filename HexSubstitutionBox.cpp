#include <string>

#include "utils.h"
#include "HexSubstitutionBox.h"

int HexSubstitutionBox::get(int row, int col)
{
    return lookup[row][col];
}
