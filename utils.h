#include <string>

unsigned char ascii_to_hex(unsigned char a);
unsigned char hex_to_ascii(unsigned char a);
std::string hex_string_to_ascii(std::string hex_string);
unsigned char ascii_to_base64(unsigned char a);
unsigned char base_64_to_ascii(unsigned char a);
std::string hex_to_base64(const std::string &str);
std::string xor_hex_pair(const std::string &a, const std::string &b);
std::string xor_hex_against_mono_char_string(const std::string &a_hex, char letter);
std::string xor_ascii_against_mono_char_string(const std::string &ascii_str, char c);
std::string xor_ascii_against_repeating_key(const std::string &ascii_str, const std::string &key);
std::string hex_encode(const std::string &message, const std::string &key);
std::string read_file_base64(const std::string &file_name);
unsigned int count_set_bit(int x);
unsigned int hamming_distance(const std::string &A, const std::string &B);
std::string get_rand_ascii(int count);