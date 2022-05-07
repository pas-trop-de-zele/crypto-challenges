#ifndef _Q14_
#define _Q14_

#include <string>

std::string get_prefix();
std::string Q14_encrypt_aes128_ecb(const std::string &prefix, const std::string &known, const std::string &unknown);
int count_common_blocks(const std::string &A, const std::string &B);
int find_prefix_length(const std::string &prefix);
void Q14();

#endif