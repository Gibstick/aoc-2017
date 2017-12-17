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

// do the generator thing, and return once a result is
// divisible by 2^mul_exp
static inline uint32_t
generator(uint64_t factor, uint64_t current, uint32_t mul_exp) {
    // gcc -O2 doesn't emit any div on x86-64
#ifdef PART2
    uint32_t result;
    while(((result = (factor * current) % INT_MAX) & mul_exp) != 1);
    return result;
#else
    return (factor * current) % INT_MAX;
#endif
}

/*
static uint32_t
generator_a(uint64_t current) {
    static uint64_t state = ;
    state = (state == 0) ? current : state;

    return state = (16807 * state) % INT_MAX;
}
*/

static inline uint32_t
generator_a(uint64_t current) {
#ifdef PART2
    // check for values that are divisible by 8
    return generator(16807, current, 2);
#else
    return generator(16807, current, 0);
#endif
}

static inline uint32_t
generator_b(uint64_t current) {
#ifdef PART2
    // check for values that are divisible by 8
    return generator(48271, current, 3);
#else
    return generator(48271, current, 0);
#endif
}

int main(void) {
    uint64_t counter = 0;
    uint32_t a = 65;
    uint32_t b = 8921;
    for (uint64_t i = 0; i < num_pairs; ++i) {
        a = generator_a(a);
        b = generator_b(b);
        //printf("%12" PRIu32 "\t%12" PRIu32 "\n", a, b);
        counter += (a & LOW_MASK) == (b & LOW_MASK);
    }
    printf("%" PRIu64 "\n", counter);
}
