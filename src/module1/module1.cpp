// src/module1/module1.cpp
#include "module1.h"
#include "module2.h"

namespace module1
{
    void callModule2()
    {
        module2::printMessage();
    }
}
