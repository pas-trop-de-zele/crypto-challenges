#include <string>

#include "utils.h"
#include "KeySchedule.h"

KeySchedule::KeySchedule(std::string key_)
{
    // NEED TO ASSERT KEYSIZE == 16
    int i = 0;
    for (int col = 0; col < 4; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            key[row][col] = key_[i++];
        }
    }
}

void KeySchedule::generate_key_rounds()
{
    for (int round = 1; round <= 10; ++round)
    {
        int first_col = round * 4;
        rot_col_upward_1(first_col - 1, first_col);
        sub_bytes(first_col);

        // XOR the first row the the first row of the first block by round constant
        int first_row = 0;
        key[first_row][first_col] ^= rcon[round];

        xor_col(first_col - 4, first_col, first_col);

        for (int col = first_col + 1; col < first_col + 4; ++col)
        {
            xor_col(col - 4, col - 1, col);
        }
    }
}

void KeySchedule::rot_col_upward_1(int col_to_rotate, int col)
{
    int first_row = 0, last_row = 3;
    uint32_t temp = key[first_row][col_to_rotate];
    for (int row = 0; row < 3; ++row)
    {
        key[row][col] = key[row + 1][col_to_rotate];
    }
    key[last_row][col] = temp;
}

void KeySchedule::sub_bytes(int col)
{
    for (int row = 0; row < 4; ++row)
    {
        int first_hex = key[row][col] >> 4;
        int second_hex = key[row][col] & 15;
        key[row][col] = sbox->get(first_hex, second_hex);
    }
}

void KeySchedule::xor_col(int colA, int colB, int colResult)
{
    for (int row = 0; row < 4; ++row)
    {
        key[row][colResult] = key[row][colA] ^ key[row][colB];
    }
}

void KeySchedule::key_round(int round)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = round * 4; col < round * 4 + 4; ++col)
        {
            std::cout << std::hex << key[row][col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

KeySchedule::~KeySchedule()
{
    delete sbox;
}