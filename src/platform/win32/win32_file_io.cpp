#include "win32_file_io.h"

#include <stdexcept>


#include "win32.h"

std::string FileIO::readFile(const std::string& fileName)
{
    OFSTRUCT fileStruct;

    fileStruct.cBytes = sizeof(OFSTRUCT);
    fileStruct.fFixedDisk = 0;
    fileStruct.nErrCode = 0;
    strcpy_s(fileStruct.szPathName, fileName.c_str());

    const auto handle = OpenFile(fileName.c_str(), &fileStruct, OF_READ);
    auto const fileSize = GetFileSize(reinterpret_cast<void*>(handle), nullptr);
    char* buffer = new char[fileSize];
    DWORD numBytesRead;

    if(!ReadFile(reinterpret_cast<void*>(handle), reinterpret_cast<void*>(buffer), fileSize, &numBytesRead, nullptr))
    {
        const unsigned err = GetLastError();
        CloseHandle(reinterpret_cast<HANDLE>(handle));
        delete[] buffer;
        throw std::runtime_error("Read File failed with error" + std::to_string(err));
    }

    auto result = std::string(buffer, buffer + fileSize);
    delete[] buffer;
    CloseHandle(reinterpret_cast<HANDLE>(handle));

    return result;
}
