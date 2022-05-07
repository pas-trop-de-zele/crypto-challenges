#ifndef _Q15_
#define _Q15_

#include <string>

void strip_padding(std::string s);
bool is_pkcs7_padded(const std::string &s);
void display_test_case(const std::string &s);

void Q15();

#endif