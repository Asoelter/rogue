#include "linux_file_io.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdexcept>

std::string FileIO::readFile(const std::string& fileName)
{
    auto const fileHandle = open(fileName.c_str(), O_RDONLY);

    if(fileHandle < 0)
    {
        throw std::runtime_error("linx_file_io.cpp: Could not open file");
    }

    struct stat stats;
    int status = stat(fileName.c_str(), &stats);
    int fileSize = 0;

    if(status == 0)
    {
        fileSize = stats.st_size;
    }

    char* buffer = new char[fileSize];

    const auto bytesRead = read(fileHandle, buffer, fileSize);

    if(bytesRead != fileSize)
    {
        close(fileHandle);
        delete[] buffer;
        throw std::runtime_error("linux_file_io.cpp: Could not read all of file");
    }

    auto result = std::string(buffer, buffer + bytesRead);

    close(fileHandle);
    delete[] buffer;

    return result;
}
