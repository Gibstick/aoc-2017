#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <assert.h>

#ifndef INIT_A
#define INIT_A 65
#endif

#ifndef INIT_B
#define INIT_B 8921
#endif

const uint64_t num_pairs =
#ifdef PART2
    5000000; // 5 million
#else
    40000000; // 40 million
#endif

const uint32_t LOW_MASK = 0x0000FFFF;

static inline uint32_t
generator_a(void) {
    static uint64_t state = INIT_A;
    do { state = (16807 * state) % INT_MAX; }
#ifdef PART2
    while (state % 4 != 0);
#else
    while (0);
#endif
    return state;
}

static inline uint32_t
generator_b(void) {
    static uint64_t state = INIT_B;
    do { state = (48271 * state) % INT_MAX; }
#ifdef PART2
    while (state % 8 != 0);
#else
    while (0);
#endif
    return state;
}

int main(void) {
    uint64_t counter = 0;
    for (uint64_t i = 0; i < num_pairs; ++i) {
        const uint32_t a = generator_a();
        const uint32_t b = generator_b();
        //printf("%12" PRIu32 "\t%12" PRIu32 "\n", a, b);
        counter += (a & LOW_MASK) == (b & LOW_MASK);
    }
    printf("%" PRIu64 "\n", counter);
}
