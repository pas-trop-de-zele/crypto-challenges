#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>

#include "AES128.h"
#include "KeySchedule.h"

AES128::AES128(std::string key_)
{
    key = new KeySchedule(key_);
    set_IV(std::vector<unsigned char>(16, 0));
}

void AES128::set_secret_message(std::string secret_message)
{
    // NEED TO ENSURE MESSAGE NOT EMPTY
    pad_pkcs(secret_message);
    blockify(secret_message, encrypt_blocks);
}

void AES128::pad_pkcs(std::string &message)
{
    int pad_count = 16 - (message.size() % 16);
    int pad_char = (pad_count == 0) ? 16 : pad_count;
    for (; pad_count > 0; --pad_count)
    {
        message += pad_char;
    }
}

void AES128::set_IV(const std::vector<unsigned char> &IV_vals)
{
    IV = new KeyBlock();
    int i = 0;
    for (int col = 0; col < 4; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            IV->set(row, col, (unsigned char)IV_vals[i++]);
        }
    }
}

void AES128::set_ciper_text(std::string ciper_text)
{
    blockify(ciper_text, decrypt_blocks);
}

void AES128::encrypt(std::string encrypt_mode)
{
    // Need to lower case all input
    if (encrypt_mode == "ecb")
    {
        encrypt_ecb();
    }
    else if (encrypt_mode == "cbc")
    {
        encrypt_cbc();
    }
}

// NEED TO MAKE SURE IV IS NOT NULLPTR
void AES128::encrypt_ecb()
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

void AES128::encrypt_cbc()
{
    for (int block_no = 0; block_no < encrypt_blocks.size(); ++block_no)
    {
        // For first block we xor with Initialization Vector
        KeyBlock *prev_block = (block_no == 0) ? IV : encrypt_blocks[block_no - 1];
        encrypt_blocks[block_no]->xor_block(prev_block);

        encrypt_blocks[block_no]->xor_block(key->key_round(0));
        for (int round = 1; round <= 10; ++round)
        {
            encrypt_blocks[block_no]->sub_bytes_all();

            encrypt_blocks[block_no]->rotate_row(1, 1);
            encrypt_blocks[block_no]->rotate_row(2, 2);
            encrypt_blocks[block_no]->rotate_row(3, 3);

            // DONT MIX COLUMNS FOR LAST ROUND
            if (round < 10)
            {
                encrypt_blocks[block_no]->mix_columns();
            }
            encrypt_blocks[block_no]->xor_block(key->key_round(round));
        }
    }
}

void AES128::decrypt(std::string decrypt_mode)
{
    if (decrypt_mode == "ecb")
    {
        decrypt_ecb();
    }
    else if (decrypt_mode == "cbc")
    {
        decrypt_cbc();
    }
}

void AES128::decrypt_ecb()
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

void AES128::decrypt_cbc()
{
    // NEED TO ENSURE THERE IS ATLEAST A BLOCK
    KeyBlock *prev_undecrypted_block = nullptr;

    for (int block_no = 0; block_no < decrypt_blocks.size(); ++block_no)
    {
        KeyBlock *current_block_clone = new KeyBlock(*decrypt_blocks[block_no]);

        for (int round = 10; round >= 1; --round)
        {

            decrypt_blocks[block_no]->xor_block(key->key_round(round));
            // DONT MIX COLUMNS FOR LAST ROUND
            if (round < 10)
            {
                decrypt_blocks[block_no]->mix_columns_inverse();
            }

            // ROTATE LEFT TO GET BACK TO BEFORE
            decrypt_blocks[block_no]->rotate_row(1, 3);
            decrypt_blocks[block_no]->rotate_row(2, 2);
            decrypt_blocks[block_no]->rotate_row(3, 1);

            decrypt_blocks[block_no]->sub_bytes_inverse_all();
        }

        // ADD ROUND KEY FOR INITIAL ROUND
        decrypt_blocks[block_no]->xor_block(key->key_round(0));

        decrypt_blocks[block_no]->xor_block(prev_undecrypted_block ? prev_undecrypted_block : IV);
        delete prev_undecrypted_block;
        prev_undecrypted_block = current_block_clone;
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

std::string AES128::show_encrypted_message()
{
    std::stringstream ss;
    for (auto block : encrypt_blocks)
    {
        for (int col = 0; col < 4; ++col)
        {
            for (int row = 0; row < 4; ++row)
            {
                ss << std::setw(2) << std::setfill('0') << std::hex << block->get(row, col);
            }
        }
    }
    return ss.str();
}

void AES128::show_decrypted_blocks()
{
    for (auto block : decrypt_blocks)
    {
        std::cout << *block << "\n";
    }
}

std::string AES128::show_decrypted_message()
{
    std::stringstream ss;
    for (auto block : decrypt_blocks)
    {
        for (int col = 0; col < 4; ++col)
        {
            for (int row = 0; row < 4; ++row)
            {
                ss << std::hex << (char)block->get(row, col);
            }
        }
    }
    return ss.str();
}

bool AES128::is_ECB_encrypted(std::string hex_encrypted_string)
{
    std::unordered_set<std::string> lookup;

    // Input is in hex form we take 32 character per block (2 hex per ascii)
    for (int i = 0; i < hex_encrypted_string.size(); i += 32)
    {
        std::string block = std::string(hex_encrypted_string.begin() + i, hex_encrypted_string.begin() + i + 32);
        if (lookup.find(block) != lookup.end())
        {
            return true;
        }
        lookup.insert(std::move(block));
    }
    return false;
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
    delete IV;
}
