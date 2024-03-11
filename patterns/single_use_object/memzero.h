#pragma once

#include <string.h>

#if defined(__STDC_LIB_EXT1__)
    #define __STDC_WANT_LIB_EXT1__ 1
    #define HAS_MEMSET_S 1
#endif

#if defined(_WIN32)
    #include <Windows.h>
    #define HAS_SECURE_ZERO_MEMORY 1
#endif

#if defined(__GLIBC__) && (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 25))
    #define HAS_EXPLICIT_BZERO 1
#endif

#if defined(__FreeBSD__) && __FreeBSD_version >= 1100037
    #define HAS_EXPLICIT_BZERO 1
#endif

#if defined(__OpenBSD__) && OpenBSD >= 201405
    #define HAS_EXPLICIT_BZERO 1
#endif

#if defined(__NetBSD__) && __NetBSD_Version__ >= 702000000
    #define HAS_EXPLICIT_MEMSET 1
#endif

inline void memzero(void *const buff, const size_t len)
{
#if defined (HAS_SECURE_ZERO_MEMORY)
    ::SecureZeroMemory(buff, len);
#elif defined (HAS_MEMSET_S)
    ::memset_s(buff, static_cast<rsize_t>(len), 0, static_cast<rsize_t>(len));
#elif defined (HAS_EXPLICIT_BZERO)
    ::explicit_bzero(buff, len);
#elif defined (HAS_EXPLICIT_MEMSET)
    ::explicit_memset(buff, 0, len);
#else
    for (auto it = reinterpret_cast<volatile unsigned char* volatile>(buff); len; ++it, --len)
        *it = 0;
#endif
}