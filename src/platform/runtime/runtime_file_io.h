#ifndef RUNTIME_FILE_IO_H
#define RUNTIME_FILE_IO_H

#ifdef ROGUE_PLATFORM_RUNTIME

#include <string>

class FileIO
{
public:
    static std::string readFile(const std::string& fileName);
};

#endif

#endif //RUNTIME_FILE_IO_H