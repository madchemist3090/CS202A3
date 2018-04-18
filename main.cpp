// Alex Olson		CS202		Assignment 3
// main.cpp		5/16/2017

/*
    This file contains the main() implementation as well as
    a welcome message. It also clears the screen upon exit.
*/

#include "data.h"

int main()
{
    int i;
    for (i = 0; i < 20; ++i) std::cout << std::endl;

    menu();
   
    for (i = 0; i < 10; ++i) std::cout << std::endl;
    return 1;
}


