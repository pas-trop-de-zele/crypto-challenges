#include <string>

#include "KeySchedule.h"
#include "AES128.h"
#include "Q7.h"

void Q7()
{
    KeySchedule *key = new KeySchedule("Thats my Kung Fu");
    key->key_round(0);
    key->generate_key_rounds();
    key->key_round(1);


    delete (key);
}