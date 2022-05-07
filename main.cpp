#include <iostream>

#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q6.h"
#include "Q7.h"
#include "Q8.h"
#include "Q9.h"
#include "Q10.h"
#include "Q11.h"
#include "Q12.h"
#include "Q13.h"
#include "Q14.h"
#include "Q15.h"

int main()
{
    int option;
    bool is_running = true;
    do
    {
        std::cout << "Select the challenge: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            Q1();
            break;
        case 2:
            Q2();
            break;
        case 3:
            Q3();
            break;
        case 4:
            Q4();
            break;
        case 5:
            Q5();
            break;
        case 6:
            Q6();
            break;
        case 7:
            Q7();
            break;
        case 8:
            Q8();
            break;
        case 9:
            Q9();
            break;
        case 10:
            Q10();
            break;
        case 11:
            Q11();
            break;
        case 12:
            Q12();
            break;
        case 13:
            Q13();
            break;
        case 14:
            Q14();
            break;
        case 15:
            Q15();
            break;
        case 'Q':
        case 'q':
            is_running = false;
            break;
        default:
            std::cout << "Please select challenger 1 - 5 or Q to quit\n";
            fflush(stdin);
        }
        std::cout << std::endl;
    } while (is_running);
}
