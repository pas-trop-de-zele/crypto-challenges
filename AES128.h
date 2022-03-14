#ifndef _AES128_
#define _AES128_

#include <string>
#include <vector>
#include "KeySchedule.h"
#include "Block.h"
#include "KeyBlock.h"
#include "RijndaelGaloisField.h"

class AES128
{
private:
    std::vector<KeyBlock *> encrypt_blocks;
    std::vector<KeyBlock *> decrypt_blocks;
    KeySchedule *key;
    std::string substitution_box[16][16];
    KeyBlock *IV;

public:
    AES128(std::string key_);
    void set_secret_message(std::string secret_message);
    void pad_pkcs(std::string &message);
    void set_IV(const std::vector<unsigned char> &IV_vals);
    void set_ciper_text(std::string ciper_text);
    void encrypt(std::string encrypt_mode);
    void encrypt_ecb();
    void encrypt_cbc();
    void decrypt(std::string decrypt_mode);
    void decrypt_ecb();
    void decrypt_cbc();
    void blockify(std::string secret, std::vector<KeyBlock *> &block_container);
    void show_encrypted_blocks();
    std::string show_encrypted_message();
    void show_decrypted_blocks();
    std::string show_decrypted_message();
    static bool is_ECB_encrypted(std::string hex_encrypted_string);
    ~AES128();
};

#endif