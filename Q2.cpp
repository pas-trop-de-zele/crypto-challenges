#include <iostream>

#include "utils.h"

void Q2()
{
	std::cout << "-------------------------------------------------Question 2------------------------------------------------" << "\n";

	// Expected 746865206B696420646F6E277420706C6179
	std::cout << xor_hex_pair("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965") << "\n";
}