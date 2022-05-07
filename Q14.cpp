#include <stdlib.h>
#include <iostream>
#include <string>

#include "Q14.h"

const int MAX_PREFIX_LENGTH = 64;

std::string valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

std::string get_prefix()
{
    std::string prefix;
    int count = rand() % MAX_PREFIX_LENGTH + 1;
    std::cout << count << "\n";
    for (; count > 0; --count)
    {
        prefix += valid_chars[rand() % valid_chars.size()];
    }
    return prefix;
}

void Q14()
{
}