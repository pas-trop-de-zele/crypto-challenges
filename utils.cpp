#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

unsigned int count_set_bit(int x)
{
    unsigned int count = 0;
    while (x)
    {
        count += (x & 1);
        x >>= 1;
    }
    return count;
}

unsigned int hamming_distance(std::string A, std::string B)
{
    if (A.size() != B.size())
    {
        std::cout << "String sizes are different"
                  << "\n";
        exit(1);
    }

    unsigned int distance = 0;
    for (int i = 0; i < A.size(); i++)
    {
        distance += count_set_bit(A[i] ^ B[i]);
    }

    return distance;
}

unsigned int ascii_to_hex(char a)
{
    a = toupper(a);
    a = (a < 58) ? a - 48 : a - 55;
    return a;
}

unsigned int hex_to_ascii(char a)
{
    a = (a < 10) ? a + 48 : a + 55;
    return a;
}

unsigned int base_64_to_ascii(char a)
{
    if (a < 26)
    {
        return a + 65;
    }
    else if (a < 52)
    {
        return a + 71;
    }
    else if (a < 62)
    {
        return a - 4;
    }
    else if (a == 62)
    {
        return 43;
    }
    else if (a == 63)
    {
        return 47;
    }
}

std::string to_base_64(const std::string &str)
{
    std::string base_64;
    int start = 0;
    for (int end = 0; end < str.size(); end++)
    {
        if (end - start + 1 == 3)
        {
            unsigned int first = ascii_to_hex(str[start]);
            unsigned int second = ascii_to_hex(str[start + 1]);
            unsigned int third = ascii_to_hex(str[start + 2]);

            first <<= 8;
            second <<= 4;

            unsigned int combine = first + second + third;
            unsigned int mask = 63;

            unsigned int first_half = (combine >> 6) & mask;
            unsigned int second_half = combine & mask;

            char char1 = (char)base_64_to_ascii(first_half);
            char char2 = (char)base_64_to_ascii(second_half);

            base_64 += char1;
            base_64 += char2;

            start = end + 1;
        }
    }
    return base_64;
}

std::string xor_hex_pair(const std::string &a, const std::string &b)
{
    std::string result;
    for (int i = 0; i < a.size(); i++)
    {
        unsigned int a_dec = ascii_to_hex(a[i]);
        unsigned int b_dec = ascii_to_hex(b[i]);
        result += hex_to_ascii(a_dec ^ b_dec);
    }
    return result;
}

std::string xor_hex_against_mono_char_string(const std::string &a_hex, char letter)
{
    if (a_hex.size() % 2)
        return "Hex input is odd";
    std::string res;

    for (int i = 0; i < a_hex.size(); i += 2)
    {
        unsigned int first = ascii_to_hex(a_hex[i]);
        unsigned int second = ascii_to_hex(a_hex[i + 1]);
        unsigned int combined = (first << 4) + second;
        res += (combined ^ letter);
    }
    return res;
}

std::string hex_encode(const std::string &message, const std::string &key)
{
    int i = 0;
    std::stringstream ss;
    for (auto chr : message)
    {
        unsigned int next_val = (unsigned char)(chr ^ key[i]);
        if (next_val < 16)
        {
            ss << "0";
        }
        ss << std::hex << next_val;
        i = (i + 1) % key.size();
    }
    return ss.str();
}