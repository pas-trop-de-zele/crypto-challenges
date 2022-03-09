#ifndef _UTILS_
#define _UTILS_

#include <string>

unsigned int ascii_to_hex(char a);
unsigned int hex_to_ascii(char a);
unsigned char ascii_to_base64(unsigned char a);
unsigned int base_64_to_ascii(char a);
std::string hex_to_base64(const std::string &str);
std::string xor_hex_pair(const std::string &a, const std::string &b);
std::string xor_hex_against_mono_char_string(const std::string &a_hex, char letter);
std::string xor_ascii_against_mono_char_string(const std::string &ascii_str, char c);
std::string xor_ascii_against_repeating_key(const std::string &ascii_str, const std::string &key);
std::string hex_encode(const std::string &message, const std::string &key);
unsigned int hamming_distance(const std::string &A, const std::string &B);
unsigned int count_set_bit(int x);

#endif