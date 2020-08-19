#ifndef FILE_IO_H
#define FILE_IO_H

#ifdef ROGUE_PLATFORM_WINDOWS
#   include <platform/win32/win32_file_io.h>
#elif defined(ROGUE_PLATFORM_LINUX)
#   include <platform/linux/linux_file_io.h>
#elif defined(ROGUE_PLATFORM_RUNTIME) || defined(ROGUE_PLATFORM_MAC)
#   include <platform/runtime/runtime_file_io.h>
#endif

class Directory
{
public:
    Directory(std::string path)
        : path_(std::move(path))
    {
        
    }

    [[nodiscard]]
    std::string pathTo(const std::string& fileName) const
    {
        return path_ + "/" + fileName;
    }

private:
    std::string path_;
};

#ifdef ROGUE_RESOURCE_DIRECTORY
    inline Directory resourceDirectory(ROGUE_RESOURCE_DIRECTORY);
#else
#error "ROGUE_RESOURCE_DIRECTORY is not defined"
#endif

#endif //FILE_IO_H
