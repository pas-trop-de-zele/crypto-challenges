#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

unsigned char ascii_to_hex(unsigned char a)
{
    a = toupper(a);
    a = (a < 58) ? a - 48 : a - 55;
    return a;
}

unsigned char hex_to_ascii(unsigned char a)
{
    a = (a < 10) ? a + 48 : a + 55;
    return a;
}

unsigned char ascii_to_base64(unsigned char a)
{
    if (a == 43)
    {
        return 62;
    }
    else if (a == 47)
    {
        return 63;
    }
    if (48 <= a && a < 58)
    {
        return a + 4;
    }
    else if (65 <= a && a < 91)
    {
        return a - 65;
    }
    else if (97 <= a && a < 123)
    {
        return a - 71;
    }
    // Replace '=' with 0 padding as ad hoc solution
    else if (a == '=')
    {
        return 48;
    }
    else
    {
        printf("%s:%d: Invalid base64 char '%c'\n", __FILE__, __LINE__, a);
        exit(-1);
    }
}

unsigned char base_64_to_ascii(unsigned char a)
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

std::string hex_to_base64(const std::string &str)
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

std::string xor_ascii_against_mono_char_string(const std::string &ascii_str, char c)
{
    std::string res;
    for (int i = 0; i < ascii_str.size(); ++i)
    {
        res += (unsigned char)(ascii_str[i] ^ c);
    }
    return res;
}

std::string xor_ascii_against_repeating_key(const std::string &ascii_str, const std::string &key)
{
    std::string res;
    int i = 0;
    for (auto ch : ascii_str)
    {
        res += (unsigned char)(ch ^ key[i]);
        i = (i + 1) % key.size();
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

unsigned int count_set_bit(int x)
{
    unsigned int count = 0;
    while (x)
    {
        ++count;
        x &= (x - 1);
    }
    return count;
}

unsigned int hamming_distance(const std::string &A, const std::string &B)
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