#ifndef XOSHIRO_PSEUDORANDOM_NUMBER_GENERATOR_CONFIG_H
#define XOSHIRO_PSEUDORANDOM_NUMBER_GENERATOR_CONFIG_H

/* Detecting compiler */

#if defined(__GNUC__)
#  define XSRPRNG_ON_GNUC 1
#  if defined(__clang__)
#    define XSRPRNG_ON_CLANG 1
#  else
#    define XSRPRNG_ON_GCC 1
#  endif
#elif defined(_MSC_VER)
#  define XSRPRNG_ON_MSVC 1
#else
#  error Unsupported compiler
#endif

/* Turning off warning "-Wlong-long" on GNUC */

#if XSRPRNG_ON_GNUC && __STDC_VERSION__ < 199901L
#  define XSRPRNG_U64_WARN_BEGIN \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wlong-long\"")
#  define XSRPRNG_U64_WARN_END \
    _Pragma("GCC diagnostic pop")
#else
#  define XSRPRNG_U64_WARN_BEGIN
#  define XSRPRNG_U64_WARN_END
#endif

/* Define fixed width integer types */

#if __STDC_VERSION__ >= 199901L

#include <stdint.h>

typedef uint32_t xsrprng_u32_t;
typedef uint64_t xsrprng_u64_t;

#else /* C89 */

#include <limits.h>

#if ULONG_MAX == 0xFFFFFFFFul
typedef unsigned long xsrprng_u32_t;
#else
typedef unsigned int  xsrprng_u32_t;
#endif

#if XSRPRNG_ON_GNUC
XSRPRNG_U64_WARN_BEGIN
typedef unsigned long long xsrprng_u64_t;
XSRPRNG_U64_WARN_END
#elif XSRPRNG_ON_MSVC
typedef unsigned __int64 xsrprng_u64_t;
#else
#  error Unsupported copmiler
#endif

#endif /* __STDC_VERSION__ >= 199901L */

#endif /* XOSHIRO_PSEUDORANDOM_NUMBER_GENERATOR_CONFIG_H */