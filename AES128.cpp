#include <string>
#include <iostream>

#include "AES128.h"
#include "KeySchedule.h"

AES128::AES128(std::string key_)
{
    key = new KeySchedule(key_);
}

void AES128::set_secret_message(std::string secret_message)
{
    blockify(secret_message, encrypt_blocks);
}

void AES128::set_ciper_text(std::string ciper_text)
{
    blockify(ciper_text, decrypt_blocks);
}

void AES128::encrypt()
{
    // ADD ROUND KEY FOR INITIAL ROUND
    for (auto block : encrypt_blocks)
    {
        block->xor_block(key->key_round(0));
    }

    for (int round = 1; round <= 10; ++round)
    {
        for (auto block : encrypt_blocks)
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

void AES128::decrypt()
{
    for (int round = 10; round >= 1; --round)
    {
        for (auto block : decrypt_blocks)
        {
            block->xor_block(key->key_round(round));
            // DONT MIX COLUMNS FOR LAST ROUND
            if (round < 10)
            {
                block->mix_columns_inverse();
            }

            // ROTATE LEFT TO GET BACK TO BEFORE
            block->rotate_row(1, 3);
            block->rotate_row(2, 2);
            block->rotate_row(3, 1);

            block->sub_bytes_inverse_all();
        }
    }

    // ADD ROUND KEY FOR INITIAL ROUND
    for (auto block : decrypt_blocks)
    {
        block->xor_block(key->key_round(0));
    }
}

void AES128::blockify(std::string secret, std::vector<KeyBlock *> &block_container)
{
    // NEED TO ENSURE INDEX NOT OUT OF BOUND

    for (int i = 0; i < secret.size();)
    {
        block_container.push_back(new KeyBlock());
        int block_no = i / 16;
        for (int col = 0; col < 4; ++col)
        {
            for (int row = 0; row < 4; ++row)
            {
                block_container[block_no]->set(row, col, (unsigned char)secret[i++]);
            }
        }
    }
}

void AES128::show_encrypted_blocks()
{
    for (auto block : encrypt_blocks)
    {
        std::cout << *block << "\n";
    }
}

void AES128::show_decrypted_blocks()
{
    for (auto block : decrypt_blocks)
    {
        std::cout << *block << "\n";
    }
}

void AES128::show_decrypted_message()
{
    for (auto block : decrypt_blocks)
    {
        for (int col = 0; col < 4; ++col)
        {
            for (int row = 0; row < 4; ++row)
            {
                std::cout << (char)block->get(row, col);
            }
        }
    }
}

AES128::~AES128()
{
    for (auto block : encrypt_blocks)
    {
        delete block;
    }
    for (auto block : decrypt_blocks)
    {
        delete block;
    }
    delete key;
}
