#include <string>
#include <iostream>

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

    unsigned char pad = s[s.size() - 1];
    for (int i = s.size() - pad; i < s.size(); ++i)
    {
        if (s[i] != pad)
            return false;
    }
    return true;
}

void Q15()
{
    std::string test = "ICE ICE BABY\x04\x04\x04\x04";
    std::cout << "Checking " << test << "\n";
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
}