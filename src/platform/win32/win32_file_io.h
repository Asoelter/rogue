#ifndef WIN32_FILE_IO_H
#define WIN32_FILE_IO_H

#include <string>

class FileIO
{
public:
    static std::string readFile(const std::string& fileName);
};

#endif //WIN32_FILE_IO_H
