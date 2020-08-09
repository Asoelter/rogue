#ifndef LINUX_FILE_IO_H
#define LINUX_FILE_IO_H

#include <string>

class FileIO
{
public:
    static std::string readFile(const std::string& fileName);
};

#endif //LINUX_FILE_IO_H
