#ifndef RUNTIME_FILE_IO_H
#define RUNTIME_FILE_IO_H

#include <string>

class FileIO
{
public:
    static std::string readFile(const std::string& fileName);
};

#endif //RUNTIME_FILE_IO_H