#include "CoreFunctions.hpp"

std::string getName(const std::string& FileName)
{
    const std::size_t FileNamePos = FileName.find_last_of('.');
    const std::size_t StringStart = 0;
    return FileName.substr(StringStart, FileNamePos);
}