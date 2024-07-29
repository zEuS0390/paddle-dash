#include <cmath>
#include <sstream>
#include "funcs.hpp"

std::string funcs::intToStr(int number) {
    std::stringstream str;
    str << number;
    return str.str();
}

float funcs::degToRad (float deg) {
    return deg * M_PI/180.0f;
}
