/* Xoshiro256**
 *
 * Size of word  - 64 bit
 * Size of state - 256 bit
 * Source:
 *   https://prng.di.unimi.it/xoshiro256starstar.c
 */

#ifndef XOSHIRO_256_STAR_STAR_PRNG_H
#define XOSHIRO_256_STAR_STAR_PRNG_H

#include "config.h"

typedef struct xoshiro256ss_t {
    xsrprng_u64_t S[4];
} xoshiro256ss_t;

void xoshiro256ss_seed(xoshiro256ss_t* state, xsrprng_u64_t seed);

xsrprng_u64_t xoshiro256ss_next(xoshiro256ss_t* state);

void xoshiro256ss_jump(xoshiro256ss_t* state);
void xoshiro256ss_ljmp(xoshiro256ss_t* state);

#endif /* XOSHIRO_256_STAR_STAR_PRNG_H */