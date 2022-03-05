#include <iostream>

#include "Q1.h";
#include "Q2.h";
#include "Q3.h";
#include "Q4.h";
#include "Q5.h";

int main()
{
    char option;
    bool is_running = true;
    do {
        std::cout << "Select the challenge: ";
        std::cin >> option;

        switch(option)
        {
            case '1':
                Q1();
                break;
            case '2':
                Q2();
                break;
            case '3':
                Q3();
                break;
            case '4':
                Q4();
                break;
            case '5':
                Q5();
                break;
            case 'Q':
            case 'q':
                is_running = false;
                break;
            default:
                std::cout << "Please select challenger 1 - 5 or Q to quit\n";
        }
        std::cout << std::endl;
    } while (is_running);

    return 0;
}
