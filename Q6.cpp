#include <iostream>
#include <fstream>
#include <limits.h>
#include <algorithm>

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
    int chosen_key = -1;
    for (int KEYSIZE = 2; KEYSIZE <= 40; ++KEYSIZE)
    {
        int blocks = input.size() / KEYSIZE;
        double edit_distance = 0;
        for (int block_no = 0; block_no < blocks - 1; ++block_no)
        {
            int first = block_no * KEYSIZE, second = first + KEYSIZE;
            for (int offset = 0; offset < KEYSIZE; ++offset)
            {
                edit_distance += count_set_bit(input[first + offset] ^ input[second + offset]);
            }
        }
        double average = (double)(edit_distance / blocks);
        double normalized = (double)(average / (KEYSIZE * 32));
        if (normalized < smallest_normalized_distance)
        {
            smallest_normalized_distance = normalized;
            chosen_key = KEYSIZE;
        }
    }
    std::cout << chosen_key << "\n";
}