// src/main.cpp
#include <iostream>
#include "module1/module1.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;

#ifdef _WIN32
    std::cout << "Running on Windows" << std::endl;
#elif __linux__
    std::cout << "Running on Linux" << std::endl;
#endif

    module1::callModule2();

    return 0;
}
