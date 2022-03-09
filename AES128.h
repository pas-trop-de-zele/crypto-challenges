#ifndef _AES128_
#define _AES128_

#include <string>
#include "KeySchedule.h"

class AES128
{
private:
    std::string secret;
    KeySchedule* key;
    std::string substitution_box[16][16];

public:
    AES128(std::string secret_, std::string key_);
    void show_key(int round);
};

#endif