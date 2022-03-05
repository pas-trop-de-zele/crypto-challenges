#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "utils.h"

void Q4()
{
    std::cout << "-------------------------------------------------Question 4------------------------------------------------" << "\n";

    int highest_rank = 0;
    std::string encoded_line;
    std::string message;
    std::ifstream input ("./Q4_input.txt");
    std::string line;
    while (std::getline(input, line))
    {
        for (int i = 0; i < 128; i++)
        {
            std::string decode = xor_hex_against_mono_char_string(line, i);
            int rank = 0;
            for (unsigned char chr : decode)
            {
                if (isalpha(chr) || chr == 32) rank++;
            }
            if (rank > highest_rank)
            {
                message = decode;
                highest_rank = rank;
                encoded_line = line;
            }
        }
    }
    std::cout << "Hidden message: " << message << "\n";
}