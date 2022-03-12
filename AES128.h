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
    std::vector<KeyBlock *> secret_blocks;
    KeySchedule *key;
    std::string substitution_box[16][16];
    RijndaelGaloisField *RGF;

public:
    AES128(std::string secret_, std::string key_);
    void encrypt();
    void blockify(std::string secret);
    void show_all_blocks();
    void show_block(int round);
    ~AES128();
};

#endif