#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#if defined(WIN32) || defined(__WIN32__) || defined(__CYGWIN32__) || defined(_MSC_VER)
#   include "../platform/win32/win32_allocator.h"
#endif

#endif //ALLOCATOR_H
