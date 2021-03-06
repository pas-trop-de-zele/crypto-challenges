#include <iostream>

#include "aes128-ecb-cbc/AES128.h"
#include "Q13.h"
#include "utils.h"

std::string profile_for(const std::string &email)
{
    std::string profile;
    profile += "email=" + email + ".com";
    profile += "&uid=10";
    profile += "&role=user";
    return profile;
}

void Q13()
{
    std::string KEY = "YELLOW SUBMARINE";
    std::unique_ptr<AES128> crypto = std::make_unique<AES128>(KEY);

    std::string email(9, 'A');
    std::string encoded_profile = profile_for(email);

    // email=AAAAAAAAA. | com&uid=10&role= | user
    std::cout << "INITIAL PROFILE: " << encoded_profile << "\n";

    crypto->set_secret_message(encoded_profile);
    crypto->encrypt("ecb");

    // first two block cut off without role user: "email=AAAAAAAAA. | com&uid=10&role="
    std::string first_two_block = (crypto->show_encrypted_message()).substr(0, 64);

    std::string admin_pad = "AAAAAAAAAAadmin";
    // pad 11 0xb to have admin on a separate block
    admin_pad += std::string(11, 0xb);

    std::string encoded_admin_pad = profile_for(admin_pad);
    crypto->set_secret_message(encoded_admin_pad);
    crypto->encrypt("ecb");

    // isolate admin block "admin"
    std::string admin_block = (crypto->show_encrypted_message()).substr(32, 32);

    // combined to get email=AAAAAAAAA. | com&uid=10&role= | admin
    std::string combined = hex_string_to_ascii(first_two_block) + hex_string_to_ascii(admin_block);
    crypto->set_ciper_text(combined);
    crypto->decrypt("ecb");

    std::cout << "ELEVATED PROFILE: " << crypto->show_decrypted_message() << "\n";
}