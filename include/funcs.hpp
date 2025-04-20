#ifndef FUNCS_H
#define FUNCS_H

#include <string>

namespace funcs
{
    std::string intToStr (int);
    std::string getExecutablePath ();
    std::string getExecutableDir ();
    std::string joinPath (const std::string&, const std::string&);  
}

#endif

