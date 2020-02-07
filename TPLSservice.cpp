// TPLSservice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <windows.h>
#include "Watchdog.h"

using namespace std;

int main(int argc, char *argv[])
{
    //Needs some more jobs to do, this lazy function
    Watch(0x8D8350);
    return 0;
}