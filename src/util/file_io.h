#ifndef FILE_IO_H
#define FILE_IO_H

#if defined(WIN32) || defined(__WIN32__) || defined(__CYGWIN32__) || defined(_MSC_VER)
#   include <platform/win32/win32_file_io.h>
#endif

#endif //FILE_IO_H
