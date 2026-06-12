#ifndef XOSHIRO_PSEUDORANDOM_NUMBER_GENERATOR_UTILS_H
#define XOSHIRO_PSEUDORANDOM_NUMBER_GENERATOR_UTILS_H

#include "config.h"

/* Bit rotation functions */

#ifdef XSRPRNG_USE_ROTL32
static xsrprng_u32_t XSRPRNG_USE_ROTL32(xsrprng_u32_t n, xsrprng_u32_t s)
    { s &= 31; return n << s | n >> (-s & 31); }
#endif

#ifdef XSRPRNG_USE_ROTR32
static xsrprng_u32_t XSRPRNG_USE_ROTR32(xsrprng_u32_t n, xsrprng_u32_t s)
    { s &= 31; return n >> s | n << (-s & 31); }
#endif

#ifdef XSRPRNG_USE_ROTL64
static xsrprng_u64_t XSRPRNG_USE_ROTL64(xsrprng_u64_t n, xsrprng_u64_t s)
    { s &= 63; return n << s | n >> (-s & 63); }
#endif

#ifdef XSRPRNG_USE_ROTR64
static xsrprng_u64_t XSRPRNG_USE_ROTR64(xsrprng_u64_t n, xsrprng_u64_t s)
    { s &= 63; return n >> s | n << (-s & 63); }
#endif

/* SplitMix functions */

#ifdef XSRPRNG_USE_SPLITMIX32
static xsrprng_u32_t XSRPRNG_USE_SPLITMIX32(xsrprng_u32_t* x) {
    xsrprng_u32_t z = (*x += 0x9e3779b9);
    z = (z ^ (z >> 15)) * 0x85ebca6b;
    z = (z ^ (z >> 13)) * 0xc2b2ae35;
    return z ^ (z >> 16);
}
#endif

#ifdef XSRPRNG_USE_SPLITMIX64
static xsrprng_u64_t XSRPRNG_USE_SPLITMIX64(xsrprng_u64_t* x) {
    xsrprng_u64_t z = (*x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}
#endif

#endif /* XOSHIRO_PSEUDORANDOM_NUMBER_GENERATOR_UTILS_H */