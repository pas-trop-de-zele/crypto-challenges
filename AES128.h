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

public:
    AES128(std::string key_);
    void set_secret_message(std::string secret_message);
    void pad_pkcs(std::string &message);
    void set_ciper_text(std::string ciper_text);
    void encrypt();
    void decrypt();
    void blockify(std::string secret, std::vector<KeyBlock *> &block_container);
    void show_encrypted_blocks();
    void show_decrypted_blocks();
    void show_decrypted_message();
    ~AES128();
};

#endif