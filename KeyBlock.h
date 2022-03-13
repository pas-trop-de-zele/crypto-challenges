#ifndef _KEY_BLOCK_
#define _KEY_BLOCK_

#include <iostream>
#include "Block.h"
#include "HexSubstitutionBox.h"

class KeyBlock : public Block
{
public:
    KeyBlock() = default;
    void rotate_row(int row, int by);
    void rotate_col(int col, int by);
    void sub_bytes_all();
    void sub_bytes_col(int col);
    void sub_bytes_inverse_all();
    void sub_bytes_inverse_col(int col);
    void xor_block(Block *block);
    void mix_columns();
    void mix_columns_inverse();
    static void copy_col(Block *source, int source_col, Block *dest, int dest_col);
    static void xor_col(Block *A, int col_A, Block *B, int col_B, Block *dest, int dest_col);
    ~KeyBlock() = default;
};

#endif