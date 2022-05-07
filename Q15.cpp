#include <string>
#include <iostream>
#include <vector>

#include "Q15.h"

void strip_padding(std::string s)
{
    unsigned char pad = s[s.size() - 1];
    for (; pad > 0; --pad)
    {
        s.pop_back();
    }
}

bool is_pkcs7_padded(const std::string &s)
{
    int BLOCK_SIZE = 16;
    if (s.size() % BLOCK_SIZE)
        return false;

    std::string last_block = s.substr(s.size() - BLOCK_SIZE, BLOCK_SIZE);
    unsigned char pad = last_block[last_block.size() - 1];
    for (int i = last_block.size() - pad; i < BLOCK_SIZE; ++i)
    {
        if (last_block[i] != pad)
            return false;
    }
    return true;
}

void display_test_case(const std::string &s)
{
    for (unsigned char c : s)
    {
        if (c <= 16)
        {
            std::cout << "\\x0" << c + 0;
        }
        else
        {
            std::cout << c;
        }
    }
    std::cout << "\n";
}

void Q15()
{
    std::vector<std::string> tests =
        {
            "ICE ICE BABY\x04\x04\x04\x04",
            "0123456789123456ICE ICE BABY\x04\x04\x04\x04",
            "0123456789123456ICE ICE \x08\x08\x08\x08\x08\x08\x08\x08",
            "ICE ICE\x09\x09\x09\x09\x09\x09\x09\x09\x09",
            "ICE\x0d\x0d\x0d\x0d\x0d\x0d\x0d\x0d\x0d\x0d\x0d\x0d\x0d",
            "I\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f",
            "ICE\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f\x0f",
            "ICE ICE BABY\x05\x05\x05\x05",
        };

    for (const std::string &test : tests)
    {
        display_test_case(test);
        if (is_pkcs7_padded(test))
        {
            strip_padding(test);
            std::cout << "Pad stripped: " << test << "\n";
        }
        else
        {
            std::cout << "NOT PADDED CORRECTLY"
                      << "\n";
        }
        std::cout << "\n";
    }
}