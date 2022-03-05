#ifndef _UTILS_
#define _UTILS_

#include <string>

unsigned int hamming_distance(std::string A, std::string B);
unsigned int count_set_bit(int x);
unsigned int ascii_to_hex(char a);
unsigned int hex_to_ascii(char a);
unsigned int base_64_to_ascii(char a);
std::string to_base_64(const std::string &str);
std::string xor_hex_pair(const std::string &a, const std::string &b);
std::string xor_hex_against_mono_char_string(const std::string &a_hex, char letter);
std::string hex_encode(const std::string &message, const std::string &key);

#endif