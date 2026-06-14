#include <stdio.h>

#include "xoshiro256ss/xoshiro256ss.h"

/* use ANSI coloring */
#if 1
#  define OK   "\x1b[32mOK\x1b[0m"
#  define FAIL "\x1b[31mFAIL\x1b[0m"
#else
#  define OK   "OK"
#  define FAIL "FAIL"
#endif

#define COMMA ,

#define test_output(name, otype, seed, aseed, ajump, aljmp) do { \
    const otype after_seed[] = aseed;                            \
    const otype after_jump[] = ajump;                            \
    const otype after_ljmp[] = aljmp;                            \
    const int aseed_sz = sizeof after_seed / sizeof *after_seed; \
    const int ajump_sz = sizeof after_jump / sizeof *after_jump; \
    const int aljmp_sz = sizeof after_ljmp / sizeof *after_ljmp; \
    name##_t s; int i, ok;                                       \
                                                                 \
    name##_seed(&s, seed);                                       \
    for (i = 0, ok = 1; i < aseed_sz; i++)                       \
        if (after_seed[i] != name##_next(&s)) { ok = 0; break; } \
    printf("- Check output after set seed ... %s\n",ok?OK:FAIL); \
                                                                 \
    name##_seed(&s, seed);                                       \
    name##_jump(&s);                                             \
    for (i = 0, ok = 1; i < ajump_sz; i++)                       \
        if (after_jump[i] != name##_next(&s)) { ok = 0; break; } \
    printf("- Check output after cal jump ... %s\n",ok?OK:FAIL); \
                                                                 \
    name##_seed(&s, seed);                                       \
    name##_ljmp(&s);                                             \
    for (i = 0, ok = 1; i < aljmp_sz; i++)                       \
        if (after_ljmp[i] != name##_next(&s)) { ok = 0; break; } \
    printf("- Check output after cal ljmp ... %s\n",ok?OK:FAIL); \
} while (0)

int main(void) {
    putchar('\n');

    /* -------------------------------------------------------------------------------- */

    puts("Testing xoshiro256**:");
    test_output(
        xoshiro256ss, xsrprng_u64_t, 100,
        { 0x0afee0773a0d8a51 COMMA 0x13b0ca759b9b1735 COMMA 0x5c76d220f8461395 COMMA 0x8852f10b70a289f7 },
        { 0x584a39c0955f49e3 COMMA 0x6864d338bfb9cf76 COMMA 0x668d3a2a6cc6e7df COMMA 0x84f95141efd529cb },
        { 0x6dec57fc81c845f8 COMMA 0x1ba582399d4ff85c COMMA 0x3abeb117fd3f8933 COMMA 0x2ac15f32911622db }
    );
    putchar('\n');

    /* -------------------------------------------------------------------------------- */

    return 0;
}