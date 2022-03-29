#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>

#include "aes128-ecb-cbc/AES128.h"
#include "Q12.h"
#include "utils.h"

std::string KEY = "YELLOW SUBMARINE";
std::string CUSTOM_INPUT(15, 'A');
std::unique_ptr<AES128> crypto = std::make_unique<AES128>(KEY);

std::string Q12_encrypt_aes128_ecb(const std::string &known, const std::string &unknown)
{
    std::string combined = known + unknown;
    crypto->set_secret_message(combined);
    crypto->encrypt("ecb");
    return crypto->show_encrypted_message();
}

void Q12()
{
    std::string unknown_input = read_file_base64("./Q12_input.txt");
    // std::string unknown_input = "THIS IS THE INPUT";

    std::unordered_map<std::string, unsigned char> lookup;

    for (int i = 0; i < 256; ++i)
    {
        std::string unknown;
        unknown += i;

        // Encrypted message would be show in hex format
        // Last 2 chars would be the hex of the hex representation of last char
        std::string encrypted = Q12_encrypt_aes128_ecb(CUSTOM_INPUT, unknown);
        std::stringstream buffer(encrypted.substr(30, 2));
        unsigned char last_two_char;
        buffer >> std::hex >> last_two_char;
        lookup[encrypted] = (unsigned char)i;
    }

    std::string input;
    for (unsigned char ch : unknown_input)
    {
        std::string unknown;
        unknown += (unsigned char)ch;

        std::string encrypted = Q12_encrypt_aes128_ecb(CUSTOM_INPUT, unknown);
        input += (unsigned char)lookup.at(encrypted);
    }

    std::cout << input << "\n";
}