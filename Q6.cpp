#include <iostream>
#include <fstream>
#include <limits.h>
#include <algorithm>
#include <string>
#include <vector>

#include "utils.h"
#include "Q6.h"

void Q6()
{
    std::string input;
    std::ifstream file("./q6_input.txt");
    std::string line;

    uint32_t mask = 255;
    while (std::getline(file, line))
    {
        for (int i = 0; i < line.size(); i = i + 4)
        {
            uint32_t first = ascii_to_base64(line[i]) << 18;
            uint32_t second = ascii_to_base64(line[i + 1]) << 12;
            uint32_t third = ascii_to_base64(line[i + 2]) << 6;
            uint32_t fourth = ascii_to_base64(line[i + 3]);
            uint32_t combine = first | second | third | fourth;

            input += combine >> 16;
            input += (combine >> 8) & mask;
            input += combine & mask;
        }
    }

    double smallest_normalized_distance = INT_MAX;
    int chosen_keysize = -1;
    for (int KEYSIZE = 2; KEYSIZE <= 40; ++KEYSIZE)
    {
        int pairs = (input.size() / KEYSIZE) - 1;
        double edit_distance = 0;
        for (int pair_no = 0; pair_no < pairs; ++pair_no)
        {
            int first = pair_no * KEYSIZE, second = first + KEYSIZE;
            for (int offset = 0; offset < KEYSIZE; ++offset)
            {
                edit_distance += count_set_bit(input[first + offset] ^ input[second + offset]);
            }
        }
        double average = (double)(edit_distance / pairs);
        double normalized = (double)(average / (KEYSIZE * 32));
        if (normalized < smallest_normalized_distance)
        {
            smallest_normalized_distance = normalized;
            chosen_keysize = KEYSIZE;
        }
    }

    printf("CHOSEN KEYSIZE: %d\n", chosen_keysize);

    std::vector<std::string> blocks(chosen_keysize, "");
    std::string repeating_key(chosen_keysize, '\0');

    // Separate into blocks
    for (int i = 0; i < input.size(); ++i)
    {
        int block_no = i % blocks.size();
        blocks[block_no] += input[i];
    }

    for (int block_no = 0; block_no < blocks.size(); ++block_no)
    {
        int rank = 0;
        unsigned char block_key = 0;
        for (int i = 0; i < 128; ++i)
        {
            std::string res = xor_ascii_against_mono_char_string(blocks[block_no], i);
            int count = 0;
            for (auto ch : res)
            {
                if (isalpha(ch) || ch == 32)
                {
                    ++count;
                }
            }
            if (count > rank)
            {
                rank = count;
                block_key = i;
            }
        }
        repeating_key[block_no] = block_key;
    }

    printf("REPEATING KEY: %s\n", repeating_key.c_str());

    std::cout << xor_ascii_against_repeating_key(input, repeating_key);
}