#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>

#include "Q8.h"
#include "aes128-ecb-cbc/AES128.h"

void Q8()
{
    std::ifstream file("./q8_input.txt");
    std::string line;

    int line_no = 0;
    while (std::getline(file, line))
    {
        if (AES128::is_ECB_encrypted(line))
        {
            std::cout << "LINE NUMBER " << line_no << " - " << line << "\n";
            return;
        }
        ++line_no;
    }
}