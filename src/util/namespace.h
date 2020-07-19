#ifndef UTIL_NAMESPACE_H
#define UTIL_NAMESPACE_H

#ifndef UTIL_NAMESPACE
#   define UTIL_NAMESPACE util
#endif 

#ifndef UTIL_NAMESPACE_BEGIN
#   define UTIL_NAMESPACE_BEGIN namespace UTIL_NAMESPACE{
#endif 

#ifndef UTIL_NAMESPACE_END
#   define UTIL_NAMESPACE_END }
#endif 

#ifndef USE_UTIL_NAMESPACE
#   define USE_UTIL_NAMESPACE using namespace UTIL_NAMESPACE;
#endif

#endif //UTIL_NAMESPACE_H
