#ifndef _BLOCK_
#define _BLOCK_

#include <iostream>
#include "HexSubstitutionBox.h"

class Block
{
    friend std::ostream &operator<<(std::ostream &os, const Block &block);

private:
    int data[4][4] = {0};
    HexSubstitutionBox *sbox;

public:
    Block();
    int get(int row, int col) const;
    void set(int row, int col, int val);
    void rotate_row(int row, int by);
    void rotate_col(int col, int by);
    void sub_bytes_all();
    void sub_bytes_col(int col);
    Block(const Block &source);
    Block(Block &&source);
    static void copy_col(Block *source, int source_col, Block *dest, int dest_col);
    static void xor_col(Block *A, int col_A, Block *B, int col_B, Block *dest, int dest_col);
    ~Block();
};

#endif