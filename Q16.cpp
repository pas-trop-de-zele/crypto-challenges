#include <string>
#include <memory>

#include "Q16.h"
#include "utils.h"
#include "aes128-ecb-cbc/AES128.h"

std::string Q16_KEY = "YELLOW SUBMARINE";
std::unique_ptr<AES128> Q16_crypto = std::make_unique<AES128>(Q16_KEY);

std::string Q16_encrypt_aes128_cbc(std::string &s)
{
    // Sanitize all ';' and '='
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == ';' || s[i] == '=')
        {
            s[i] = '_';
        }
    }
    std::string pre = "comment1=cooking%20MCs;userdata=";
    std::string post = ";comment2=%20like%20a%20pound%20of%20bacon";
    std::string combined = pre + s + post;

    Q16_crypto->set_secret_message(combined);
    Q16_crypto->encrypt("cbc");
    return Q16_crypto->show_encrypted_message();
}

void Q16()
{
    std::string input = "_admin_true";

    std::string encrypted = Q16_encrypt_aes128_cbc(input);

    std::cout << "Cipher text: " << encrypted << "\n";
    /**
     * Since our input would be on block 3 and we need to
     * flip first _ to ; (0th index bit) and second _ to : (6th index bit)
     *
     * We will modify the cipher text for previous block (block 2)
     * on according bit position (0th index and 6th index)
     */

    std::string second_block_cipher = encrypted.substr(32, 32);
    std::string target_block_cipher = encrypted.substr(64, 32);

    unsigned char zero_index_before_xor = hex_string_to_ascii(second_block_cipher.substr(0, 2))[0] ^ input[0];
    unsigned char sixth_index_before_xor = hex_string_to_ascii(second_block_cipher.substr(12, 2))[0] ^ input[6];

    std::cout << std::hex << "Target block zero_index before xor: " << zero_index_before_xor + 0 << "\n";
    std::cout << std::hex << "Target block sixth_index before xor: " << sixth_index_before_xor + 0 << "\n";

    std::cout << "Second block before flip:\n"
              << second_block_cipher << "\n";

    std::stringstream ss;
    ss << std::hex << (zero_index_before_xor ^ ';');
    second_block_cipher.replace(0, 2, ss.str());

    ss.str("");
    ss << std::hex << (sixth_index_before_xor ^ '=');
    second_block_cipher.replace(12, 2, ss.str());

    std::cout << "Second block after flip 0th and 6th (every position is a hex consist 2 chars):\n"
              << second_block_cipher << "\n";

    encrypted.replace(32, 32, second_block_cipher);

    encrypted = hex_string_to_ascii(encrypted);
    Q16_crypto->set_ciper_text(encrypted);
    Q16_crypto->decrypt("cbc");
    std::cout << "Decrypted string NOW HAS \";admin=true;\":\n\n"
              << Q16_crypto->show_decrypted_message() << "\n";
}