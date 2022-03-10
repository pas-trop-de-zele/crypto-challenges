#include <string>
#include <iostream>

#include "KeySchedule.h"
#include "AES128.h"
#include "Q7.h"

void Q7()
{
    KeySchedule *key = new KeySchedule("Thats my Kung Fu");
    std::cout << "Key in block\n";
    key->key_round(0);

    key->generate_key_rounds();

    for (int round = 1; round <= 10; ++round)
    {
        std::cout << "\n";
        key->key_round(round);
    }

    delete (key);
}