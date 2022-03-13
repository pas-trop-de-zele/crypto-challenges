#include <iomanip>

#include "KeyBlock.h"
#include "RijndaelGaloisField.h"

void KeyBlock::rotate_row(int row, int by)
{
    int first_col = 0, last_col = 3;
    for (; by > 0; --by)
    {
        int temp = this->get(row, first_col);
        for (int col = 0; col < 3; ++col)
        {
            int next_col = this->get(row, col + 1);
            this->set(row, col, next_col);
        }
        this->set(row, last_col, temp);
    }
}

void KeyBlock::rotate_col(int col, int by)
{
    int first_row = 0, last_row = 3;
    for (; by > 0; --by)
    {
        int temp = this->get(first_row, col);
        for (int row = 0; row < 3; ++row)
        {
            int below = this->get(row + 1, col);
            this->set(row, col, below);
        }
        this->set(last_row, col, temp);
    }
}

void KeyBlock::sub_bytes_all()
{
    for (int col = 0; col < 4; ++col)
    {
        sub_bytes_col(col);
    }
}

void KeyBlock::sub_bytes_col(int col)
{
    for (int row = 0; row < 4; ++row)
    {
        uint8_t sub_value = HexSubstitutionBox::sub(this->get(row, col));
        this->set(row, col, sub_value);
    }
}

void KeyBlock::sub_bytes_inverse_all()
{
    for (int col = 0; col < 4; ++col)
    {
        sub_bytes_inverse_col(col);
    }
}

void KeyBlock::sub_bytes_inverse_col(int col)
{
    for (int row = 0; row < 4; ++row)
    {
        uint8_t sub_value = HexSubstitutionBox::sub_inverse(this->get(row, col));
        this->set(row, col, sub_value);
    }
}

void KeyBlock::xor_block(Block *other)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            int current = this->get(row, col);
            int other_obj = other->get(row, col);

            this->set(row, col, this->get(row, col) ^ other->get(row, col));
        }
    }
}

void KeyBlock::mix_columns()
{
    Block *clone = new Block(*this);
    for (int A_row = 0; A_row < 4; ++A_row)
    {
        for (int mult_col = 0; mult_col < 4; ++mult_col)
        {
            int mult_row = 0;
            int val = 0;
            for (int A_col = 0; A_col < 4; ++A_col)
            {
                int R_multiplier = RijndaelGaloisField::data[A_row][A_col];
                val ^= RijndaelGaloisField::lookup_table[R_multiplier][clone->get(mult_row, mult_col)];
                ++mult_row;
            }
            this->set(A_row, mult_col, val);
        }
    }
    delete clone;
}

void KeyBlock::mix_columns_inverse()
{
    Block *clone = new Block(*this);
    for (int A_row = 0; A_row < 4; ++A_row)
    {
        for (int mult_col = 0; mult_col < 4; ++mult_col)
        {
            int mult_row = 0;
            int val = 0;
            for (int A_col = 0; A_col < 4; ++A_col)
            {
                int R_multiplier = RijndaelGaloisField::data_inverse[A_row][A_col];
                val ^= RijndaelGaloisField::lookup_table[R_multiplier][clone->get(mult_row, mult_col)];
                ++mult_row;
            }
            this->set(A_row, mult_col, val);
        }
    }
    delete clone;
}

void KeyBlock::copy_col(Block *source, int source_col, Block *dest, int dest_col)
{
    for (int row = 0; row < 4; ++row)
    {
        dest->set(row, dest_col, source->get(row, source_col));
    }
}

void KeyBlock::xor_col(Block *A, int col_A, Block *B, int col_B, Block *dest, int dest_col)
{
    for (int row = 0; row < 4; ++row)
    {
        dest->set(row, dest_col, A->get(row, col_A) ^ B->get(row, col_B));
    }
}
