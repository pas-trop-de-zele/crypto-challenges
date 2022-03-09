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
    for (int round = 1; round <= 1; ++round)
    {
        int col = round * 4;
        std::string rotted_col[4] = {""};
        rot_col_upward_1(col - 1, rotted_col);

    }
}

void KeySchedule::rot_col_upward_1(int col, std::string rotted_col[])
{
    int first_row = 0, last_row = 3;
    uint32_t temp = key[first_row][col];
    for (int row = 0; row < 3; ++row)
    {
        rotted_col[row] = key[row + 1][col]; 
    }
    rotted_col[last_row] = temp;
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