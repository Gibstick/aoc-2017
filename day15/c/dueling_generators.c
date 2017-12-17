#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <assert.h>

const uint64_t num_pairs =
#ifdef PART2
    5; // 5 million
#else
    40000000; // 40 million
#endif

const uint32_t LOW_MASK = 0x0000FFFF;

static inline uint32_t
generator_a(void) {
    static uint64_t state = 65;
    return state = (16807 * state) % INT_MAX;
}

static inline uint32_t
generator_b(void) {
    static uint64_t state = 8921;
    return state = (48271 * state) % INT_MAX;
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
