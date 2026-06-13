#define XSRPRNG_USE_SPLITMIX64 xsr256ssi_splitmit
#define XSRPRNG_USE_ROTL64 xsr256ssi_rotl

#include "xoshiro256ss.h"
#include "utils.h"

static const xsrprng_u64_t dflt_jump_consts[4];
static const xsrprng_u64_t long_jump_consts[4];

static void xsr256ssi_jump_base(xoshiro256ss_t* state, const xsrprng_u64_t jumps[4]) {
    xsrprng_u64_t s[4] = {0}; int i, b;

    for (i = 0; i < 4; i++)
        for (b = 0; b < 64; b++) {
            if (jumps[i] & ((xsrprng_u64_t)1 << b)) {
                s[0] ^= state->S[0];
                s[1] ^= state->S[1];
                s[2] ^= state->S[2];
                s[3] ^= state->S[3];
            }
            (void)xoshiro256ss_next(state);
        }

    state->S[0] = s[0];
    state->S[1] = s[1];
    state->S[2] = s[2];
    state->S[3] = s[3];
}

void xoshiro256ss_seed(xoshiro256ss_t* state, xsrprng_u64_t seed) {
    state->S[0] = xsr256ssi_splitmit(&seed);
    state->S[1] = xsr256ssi_splitmit(&seed);
    state->S[2] = xsr256ssi_splitmit(&seed);
    state->S[3] = xsr256ssi_splitmit(&seed);
}

xsrprng_u64_t xoshiro256ss_next(xoshiro256ss_t* state) {
    const xsrprng_u64_t out = xsr256ssi_rotl(state->S[1] * 5, 7) * 9;

    const xsrprng_u64_t t = state->S[1] << 17;
    state->S[2] ^= state->S[0];
    state->S[3] ^= state->S[1];
    state->S[1] ^= state->S[2];
    state->S[0] ^= state->S[3];
    state->S[2] ^= t;
    state->S[3] = xsr256ssi_rotl(state->S[3], 45);

    return out;
}

void xoshiro256ss_jump(xoshiro256ss_t* state) {
    xsr256ssi_jump_base(state, dflt_jump_consts);
}

void xoshiro256ss_ljmp(xoshiro256ss_t* state) {
    xsr256ssi_jump_base(state, long_jump_consts);
}

XSRPRNG_U64_WARN_BEGIN

static const xsrprng_u64_t dflt_jump_consts[4] = {
    0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c
};

static const xsrprng_u64_t long_jump_consts[4] = {
    0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635
};

XSRPRNG_U64_WARN_END