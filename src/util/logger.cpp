#include "util/logger.h"
#include <iostream>

namespace Logger
{
    void logString(char const* message) {
        std::cout << message << std::endl;
    }

    void logInt(int message) {
        std::cout << message << std::endl;
    }
}
