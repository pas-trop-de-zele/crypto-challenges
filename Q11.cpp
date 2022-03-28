#include <random>
#include <memory>

#include "Q11.h"
#include "aes128-ecb-cbc/AES128.h"
#include "utils.h"

void Q11()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> padding_count_rand(5, 10);
    std::uniform_int_distribution<> encryption_mode_rand(0, 1);

    std::string key = get_rand_ascii(16);
    int padding_count = padding_count_rand(gen);
    std::string padding = get_rand_ascii(padding_count);

    std::unique_ptr<AES128> cryptool(new AES128(key));
    // 44 Identical A to make sure we would alwways get 2 identical block in case of ECB
    std::string text(44, 'A');
    text.insert(0, padding);
    text += padding;
    cryptool->set_secret_message(text);
    std::cout << "Padding count " << padding_count * 2 << "(" << padding_count << " on each side)"
              << "\n";
    std::cout << "Text size " << text.size() << "\n";

    std::string encryption_mode = (encryption_mode_rand(gen) == 0) ? "ecb" : "cbc";
    cryptool->encrypt(encryption_mode);
    std::cout << "Encryption mode " << encryption_mode << "\n";
    std::string hex_cipher_text = cryptool->show_encrypted_message();
    std::cout << "Cipher text: " << hex_cipher_text << "\n";
    std::cout << "Predict encryption mode: " << (AES128::is_ECB_encrypted(hex_cipher_text) ? "ECB" : "CBC") << "\n";
}
