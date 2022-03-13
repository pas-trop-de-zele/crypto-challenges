#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>

#include "Q8.h"

void Q8()
{
    std::ifstream file("./q8_input.txt");
    std::string line;

    std::unordered_set<std::string> blocks;

    int line_no = 0;
    while (std::getline(file, line))
    {
        // Input is in hex form we take 32 character per block (2 hex per ascii)
        for (int i = 0; i < line.size(); i += 32)
        {
            std::string block = std::string(line.begin() + i, line.begin() + i + 32);
            if (blocks.find(block) != blocks.end())
            {
                std::cout << "LINE NUMBER: " << line_no << " - " << line << "\n";
                exit(0);
            }
            blocks.insert(std::move(block));
        }
        blocks.clear();
        ++line_no;
    }
}