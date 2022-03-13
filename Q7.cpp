#include <string>
#include <iostream>

#include "AES128.h"
#include "utils.h"

void Q7()
{
    std::string input = read_file_base64("./q7_input.txt");
    AES128 *cryptool = new AES128("YELLOW SUBMARINE");
    cryptool->set_ciper_text(input);
    cryptool->decrypt();
    cryptool->show_decrypted_message();
    delete (cryptool);
}