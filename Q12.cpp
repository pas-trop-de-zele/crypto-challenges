#include "aes128-ecb-cbc/AES128.h"
#include "Q12.h"
#include "utils.h"
#include <string>

std::string Q12_encrypt_aes128_ecb(std::string known, std::string unknown, std::string key)
{
    AES128 crypto(key);
    std::string combined = known + unknown;
    crypto.set_secret_message(combined);
    crypto.encrypt_ecb();
    return crypto.show_encrypted_message();
}

void Q12()
{
    std::string KEY = "YELLOW SUBMARINE";
    std::string input = read_file_base64("./Q12_input.txt");
    std::cout << Q12_encrypt_aes128_ecb("AAAAAAAAAAAAAAAA", input, KEY);
}