#ifndef _KEY_SCHEDULE_
#define _KEY_SCHEDULE_

#include <string>
#include <vector>

#include "Block.h"
#include "HexSubstitutionBox.h"

class KeySchedule
{
private:
    std::vector<Block *> keys;
    int round = 0;
    int rcon[11] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};
    HexSubstitutionBox *sbox;

public:
    KeySchedule(std::string key_);
    void generate_key_rounds();
    void key_round(int round);

    ~KeySchedule();
};

#endif