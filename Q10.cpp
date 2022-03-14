#include <string>
#include <iostream>
#include <vector>

#include "AES128.h"
#include "utils.h"
#include "Q10.h"

void Q10()
{
    std::string cipher_text = read_file_base64("./q10_input.txt");
    AES128 *cryptool = new AES128("YELLOW SUBMARINE");
    std::vector<unsigned char> IVs(16, 0);
    cryptool->set_IV(IVs);
    cryptool->set_ciper_text(cipher_text);
    cryptool->decrypt("cbc");
    cryptool->show_decrypted_message();
    delete (cryptool);
}