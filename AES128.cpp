#include <string>
#include <iostream>

#include "AES128.h"
#include "KeySchedule.h"
#include "RijndaelGaloisField.h"

AES128::AES128(std::string secret_, std::string key_)
{
    // MAY NEED TO ADD EXTRA BLOCK TO PAD LEFT OVER CHARS
    for (int i = 0; i < secret_.size() / 16; ++i)
    {
        secret_blocks.push_back(new KeyBlock());
    }
    key = new KeySchedule(key_);
    RGF = new RijndaelGaloisField();
    blockify(secret_);
}

void AES128::encrypt()
{
    // ADD ROUND KEY FOR INITIAL ROUND
    for (auto block : secret_blocks)
    {
        block->xor_block(key->key_round(0));
    }

    for (int round = 1; round <= 10; ++round)
    {
        for (auto block : secret_blocks)
        {
            block->sub_bytes_all();

            block->rotate_row(1, 1);
            block->rotate_row(2, 2);
            block->rotate_row(3, 3);

            // DONT MIX COLUMNS FOR LAST ROUND
            if (round < 10)
            {
                block->mix_columns();
            }
            block->xor_block(key->key_round(round));
        }
    }
}

void AES128::blockify(std::string secret)
{
    // NEED TO ENSURE INDEX NOT OUT OF BOUND
    for (int block = 0; block < secret.size(); block += 16)
    {
        int i = block;
        for (int col = 0; col < 4; ++col)
        {
            for (int row = 0; row < 4; ++row)
            {
                secret_blocks[block]->set(row, col, secret[i++]);
            }
        }
    }
}

void AES128::show_all_blocks()
{
    for (auto block : secret_blocks)
    {
        std::cout << *block << "\n";
    }
}

void AES128::show_block(int round)
{
    // NEED TO ENSURE VALID ROUND
    std::cout << *secret_blocks[round] << "\n";
}

AES128::~AES128()
{
    for (auto block : secret_blocks)
    {
        delete block;
    }
    delete key;
}
