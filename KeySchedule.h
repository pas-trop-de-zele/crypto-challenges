#ifndef _KEY_SCHEDULE_
#define _KEY_SCHEDULE_

#include <string>

class KeySchedule
{
private:
    uint32_t key[4][44];
    int round = 0;
public:
    KeySchedule(std::string key_);
    void generate_key_rounds();
    void rot_col_upward_1(int col, std::string rotted_col[]);
    void key_round(int round);
};

#endif