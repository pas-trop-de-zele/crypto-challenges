#include <stdlib.h>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <unordered_map>

#include "Q14.h"
#include "utils.h"
#include "aes128-ecb-cbc/AES128.h"

int BLOCK_SIZE = 16;
std::string VALID_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
const int MAX_PREFIX_LENGTH = 64;
std::string Q14_KEY = "YELLOW SUBMARINE";
std::unique_ptr<AES128> Q14_crypto = std::make_unique<AES128>(Q14_KEY);
std::string unknown_input = read_file_base64("./Q14_input.txt");

std::string get_random_prefix()
{
    std::string prefix;
    int count = rand() % MAX_PREFIX_LENGTH + 1;
    for (; count > 0; --count)
    {
        prefix += VALID_CHARS[rand() % VALID_CHARS.size()];
    }
    return prefix;
}

std::string Q14_encrypt_aes128_ecb(const std::string &prefix, const std::string &known, const std::string &unknown)
{
    std::string combined = prefix + known + unknown;
    Q14_crypto->set_secret_message(combined);
    Q14_crypto->encrypt("ecb");
    return Q14_crypto->show_encrypted_message();
}

int count_common_blocks(const std::string &A, const std::string &B)
{
    int count = 0;
    for (int i = 0; i < std::min(A.size(), B.size()); i += 32)
    {
        std::string A_block = A.substr(i, 32);
        std::string B_block = B.substr(i, 32);
        if (A_block != B_block)
        {
            break;
        }
        ++count;
    }
    return count;
}

int find_prefix_length(const std::string &prefix)
{
    // 0 char in known string
    std::string base_line_encryption = Q14_encrypt_aes128_ecb(prefix, "", unknown_input);
    // 1 char in known string
    std::string prev_encryption = Q14_encrypt_aes128_ecb(prefix, "A", unknown_input);

    int prev_common_block_counts = count_common_blocks(base_line_encryption, prev_encryption);
    for (int i = 2; i <= BLOCK_SIZE; ++i)
    {
        std::string curr_encryption = Q14_encrypt_aes128_ecb(prefix, std::string(i, 'A'), unknown_input);
        int common = count_common_blocks(prev_encryption, curr_encryption);
        if (common != prev_common_block_counts)
        {
            return BLOCK_SIZE * prev_common_block_counts + (BLOCK_SIZE - i + 1);
        }
        prev_encryption = curr_encryption;
        prev_common_block_counts = common;
    }
    return BLOCK_SIZE * prev_common_block_counts;
}

void Q14()
{
    std::string prefix = get_random_prefix();

    std::cout << "PREFIX LENGTH: " << prefix.size() << "\n";
    std::cout << "PREFIX: " << prefix << "\n";

    int prefix_length = find_prefix_length(prefix);
    std::cout << "DETECT PREFIX LENGTH: " << prefix_length << "\n";

    // Padding required to make unknown char the last bit in block
    // Example: prefix_length = 8
    // Needs to pad BLOCK_SIZE - 1 - (prefix_length % BLOCK_SIZE)  
    //                    = 16 - 1 - 8 = 7 extra letter to form 15 char + 1 unknown
    int padding_needed = BLOCK_SIZE - 1 - (prefix_length % BLOCK_SIZE);
    std::string CUSTOM_INPUT(padding_needed, 'A');

    // BUILD DICTIONARY WITH EACH OF 256 CHARS
    std::unordered_map<std::string, unsigned char> lookup;
    for (int i = 0; i < 256; ++i)
    {
        std::string unknown;
        unknown += i;

        std::string encrypted = Q14_encrypt_aes128_ecb(prefix, CUSTOM_INPUT, unknown);
        lookup[encrypted] = (unsigned char)i;
    }

    // Look up char using pre-built dictionary to form input
    std::string input;
    for (unsigned char ch : unknown_input)
    {
        std::string unknown;
        unknown += (unsigned char)ch;

        std::string encrypted = Q14_encrypt_aes128_ecb(prefix, CUSTOM_INPUT, unknown);
        input += (unsigned char)lookup.at(encrypted);
    }

    std::cout << input << "\n";
}