#ifndef FILE_IO_H
#define FILE_IO_H

#ifdef ROGUE_PLATFORM_WINDOWS
#   include <platform/win32/win32_file_io.h>
#elif defined(ROGUE_PLATFORM_LINUX)
#   include <platform/runtime/runtime_file_io.h>
#endif

#endif //FILE_IO_H
