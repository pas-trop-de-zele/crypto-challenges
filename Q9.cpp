#include <string>
#include <memory>

#include "Q9.h"
#include "aes128-ecb-cbc/AES128.h"

void Q9()
{
    std::string message = "Two One Nine Two";
    std::string key = "Thats my Kung Fu";
    std::unique_ptr<AES128> crypto = std::make_unique<AES128>(key);
    crypto->set_secret_message(message);
    crypto->encrypt("ecb");

    std::string encrypted = crypto->show_encrypted_message();
    std::cout << std::setw(32) << encrypted.substr(0, 32) << "|" << std::setw(32) << encrypted.substr(32, 32) << "\n";
    std::cout << std::setw(32) << "ORIGINAL STRING"       << "|" << std::setw(32) << "PADDED" << "\n";
}