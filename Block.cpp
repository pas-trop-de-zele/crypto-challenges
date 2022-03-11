#include "Block.h"

Block::Block()
    : sbox(new HexSubstitutionBox()){};

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

void Block::rotate_row(int row, int by)
{
    int first_col = 0, last_col = 3;
    for (; by > 0; --by)
    {
        int temp = data[row][first_col];
        for (int col = 0; col < 3; ++col)
        {
            data[row][col] = data[row][col + 1];
        }
        data[row][last_col] = temp;
    }
}

void Block::rotate_col(int col, int by)
{
    int first_row = 0, last_row = 3;
    for (; by > 0; --by)
    {
        int temp = data[first_row][col];
        for (int row = 0; row < 3; ++row)
        {
            data[row][col] = data[row + 1][col];
        }
        data[last_row][col] = temp;
    }
}

void Block::sub_bytes_all()
{
    for (int col = 0; col < 4; ++col)
    {
        sub_bytes_col(col);
    }
}

void Block::sub_bytes_col(int col)
{
    for (int row = 0; row < 4; ++row)
    {
        data[row][col] = sbox->sub(data[row][col]);
    }
}

Block::Block(const Block &source)
{
    std::cout << "COPIED\n";
}

Block::Block(Block &&source)
{
    std::cout << "MOVED\n";
}

void Block::copy_col(Block *source, int source_col, Block *dest, int dest_col)
{
    for (int row = 0; row < 4; ++row)
    {
        dest->set(row, dest_col, source->get(row, source_col));
    }
}

void Block::xor_col(Block *A, int col_A, Block *B, int col_B, Block *dest, int dest_col)
{
    for (int row = 0; row < 4; ++row)
    {
        dest->set(row, dest_col, A->get(row, col_A) ^ B->get(row, col_B));
    }
}

std::ostream &operator<<(std::ostream &os, const Block &block)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            os << std::hex << block.get(row, col) << " ";
        }
        os << "\n";
    }
    return os;
}

Block::~Block()
{
    delete sbox;
}