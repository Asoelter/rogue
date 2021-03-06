#ifdef ROGUE_PLATFORM_RUNTIME

#include "runtime_file_io.h"

#include <cstdio>
#include <stdexcept>

std::string FileIO::readFile(const std::string& fileName)
{
    FILE* fileHandle = fopen(fileName.c_str(), "r");

    if(!fileHandle)
    {
        throw std::runtime_error("runtime_file_io.cpp: Could not open file");
    }

    fseek(fileHandle, 0, SEEK_END);
    const auto fileSize = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);
    
    char* buffer = new char[fileSize];
    const auto amountRead = fread(buffer, sizeof(char), fileSize, fileHandle);

    auto rval = std::string(buffer, buffer + amountRead);
    delete[] buffer;
    return rval;
}

#endif
