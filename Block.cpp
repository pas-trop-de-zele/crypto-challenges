#include "Block.h"

int Block::get(int row, int col) const
{
    // NEED TO CHECK FOR OUT OF BOUND
    return data[row][col];
}

void Block::set(int row, int col, int val)
{
    // NEED TO CHECK FOR OUT OF BOUND
    data[row][col] = val;
}

Block::Block(const Block &source)
{
    // std::cout << "BLOCK COPIED";
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            data[row][col] = source.get(row, col);
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Block &block)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            os << std::setw(2) << std::setfill('0') << std::hex << block.get(row, col) << " ";
        }
        os << "\n";
    }
    return os;
}