#include <string>
#include <iostream>

#include "KeySchedule.h"
#include "HexSubstitutionBox.h"

KeySchedule::KeySchedule(std::string key_)
{
    for (int i = 0; i < 11; ++i)
    {
        keys.push_back(new Block());
    }
    sbox = new HexSubstitutionBox();

    // NEED TO ASSERT KEYSIZE == 16
    int FIRST_BLOCK = 0;
    int i = 0;
    for (int col = 0; col < 4; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            keys[FIRST_BLOCK]->set(row, col, key_[i++]);
        }
    }
}

void KeySchedule::generate_key_rounds()
{
    for (int round = 1; round <= 10; ++round)
    {
        Block *prev_block = keys[round - 1];
        Block *curr_block = keys[round];

        Block::copy_col(prev_block, 3, curr_block, 0);

        curr_block->sub_bytes_col(0);
        curr_block->rotate_col(0, 1);

        // XOR first cell of block with rcon
        curr_block->set(0, 0, curr_block->get(0, 0) ^ rcon[round]);

        Block::xor_col(prev_block, 0, curr_block, 0, curr_block, 0);
        Block::xor_col(prev_block, 1, curr_block, 0, curr_block, 1);
        Block::xor_col(prev_block, 2, curr_block, 1, curr_block, 2);
        Block::xor_col(prev_block, 3, curr_block, 2, curr_block, 3);
    }
}

void KeySchedule::key_round(int round)
{
    std::cout << *keys[round];
}

KeySchedule::~KeySchedule()
{
    for (auto block : keys)
    {
        delete block;
    }
    delete sbox;
}