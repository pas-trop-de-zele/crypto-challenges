#include <string>
#include <iostream>

#include "aes128-ecb-cbc/AES128.h"
#include "utils.h"

void Q7()
{
    std::string input = read_file_base64("./q7_input.txt");
    AES128 *cryptool = new AES128("YELLOW SUBMARINE");
    cryptool->set_ciper_text(input);
    cryptool->decrypt("ecb");
    std::cout << cryptool->show_decrypted_message() << "\n";
    delete (cryptool);
}