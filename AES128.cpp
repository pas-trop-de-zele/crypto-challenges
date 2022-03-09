#include <string>
#include <iostream>

#include "utils.h"
#include "KeySchedule.h"
#include "AES128.h"

AES128::AES128(std::string secret_, std::string key_)
    : secret(secret_)
{
    key = new KeySchedule(key_);
}

void AES128::show_key(int round)
{
    key->key_round(round);
}

AES128::~AES128()
{
    delete key;
}
