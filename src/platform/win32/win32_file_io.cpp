#include "win32_file_io.h"

#include "win32.h"

std::string FileIO::readFile(const std::string& fileName)
{
    OFSTRUCT fileStruct;

    fileStruct.cBytes = sizeof(OFSTRUCT);
    fileStruct.fFixedDisk = 0;
    fileStruct.nErrCode = 0;
    strcpy_s(fileStruct.szPathName, fileName.c_str());

    const auto handle = OpenFile(fileName.c_str(), &fileStruct, OF_READ);
    auto const fileSize = GetFileSize((void*)handle, nullptr);
    std::string rval;
    rval.reserve(fileSize);
    DWORD numBytesRead;

    if(!ReadFile((void*)handle, (void*)rval.c_str(), fileSize, &numBytesRead, nullptr))
    {
        unsigned err = GetLastError();
        char buf[256];
        snprintf(buf, 256, "Read File failed with error: %u", err);
        MessageBox(NULL, buf, "Error reading file", NULL);
    }

    return rval;
}
