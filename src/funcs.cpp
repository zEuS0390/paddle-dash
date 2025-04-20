#include <cmath>
#include <sstream>
#include "funcs.hpp"

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <unistd.h>
#endif

std::string funcs::getExecutablePath ()
{
    char buffer[1024];

#ifdef _WIN32
    GetModuleFileNameA(nullptr, buffer, sizeof(buffer));
#elif __linux__
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) buffer[len] = '\0';
#endif

    return std::string(buffer);
}

std::string funcs::getExecutableDir() {
    std::string path = getExecutablePath();
    size_t slash = path.find_last_of("/\\");
    return path.substr(0, slash);
}

std::string funcs::joinPath (const std::string& dir, const std::string& file)
{
    if (dir.empty()) return file;

    char sep =
#ifdef _WIN32
        '\\';
#else
        '/';
#endif

    if (dir.back() == sep)
    {
        return dir + file;
    }
    else
    {
        return dir + sep + file;
    }
}

std::string funcs::intToStr(int number)
{
    std::stringstream str;
    str << number;
    return str.str();
}

