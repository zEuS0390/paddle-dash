#include <cmath>
#include <sstream>
#include "funcs.hpp"

std::string funcs::intToStr(int number)
{
    std::stringstream str;
    str << number;
    return str.str();
}

