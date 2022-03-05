#include <iostream>

#include "utils.h"

void Q3()
{
    std::cout << "-------------------------------------------------Question 3------------------------------------------------" << "\n";
    int highest_rank = 0;
    std::string message;
    for (int i = 0; i < 128; i++)
    {
        std::string decode = xor_hex_against_mono_char_string("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", i);
        int rank = 0;

        // Rank base on how many char or digit or space output has
        for (unsigned char chr : decode)
        {
            if (isalpha(chr) || chr == 32) rank++;
        }
        if (rank > highest_rank)
        {
            message = decode;
            highest_rank = rank;
        }
    }

    std::cout << message << "\n";
}