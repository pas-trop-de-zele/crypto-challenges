#include <iostream>
#include <string>

#include "utils.h"

void Q1()
{
    std::cout << "-------------------------------------------------Question 1------------------------------------------------"
              << "\n";

    // Expected SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
    std::string test2 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::cout << hex_to_base64(test2) << "\n";
}
