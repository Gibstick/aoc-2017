#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

const uint16_t ARR_SIZE = UINT8_MAX + 1;
const int ROUNDS = 64;

// reverse the order of len elements in the circular array
// starting at the current position
// and return the new position
uint8_t
reverse(uint8_t arr[const static ARR_SIZE], uint8_t len, uint8_t pos, uint16_t skip_size) {
    uint8_t lo = pos;
    uint8_t hi = pos + len - 1;
    for (int i = 0; i < len / 2; ++i) {
        uint8_t temp = arr[lo];
        arr[lo] = arr[hi];
        arr[hi] = temp;
        ++lo; --hi;
    }

    return (uint8_t)pos + len + skip_size;
}

void
print_arr(uint8_t arr[const static ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE - 1; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[ARR_SIZE - 1]);
}


int
main(void) {
    uint8_t arr[ARR_SIZE];
    uint8_t cur = 0;
    uint16_t skip_size = 0;
    for (int i = 0; i < ARR_SIZE; ++i) {
        arr[i] = i;
    }

#ifdef PART2
    char suffix[] = {17, 31, 73, 47, 23};
    char input_str[256] = {0};
    const char *ret = fgets(input_str, sizeof(input_str), stdin);
    assert(ret == input_str);
    assert(feof(stdin) == 0 && "String too big");
    for (int i = 0; i < sizeof(input_str); ++i) {
        if (input_str[i] == '\n') {
            input_str[i] = '\0';
            break;
        }
    }
#endif

    uint16_t len;
#ifdef PART2
    for (int i = 0; i < ROUNDS; ++i) {
    int input_idx = 0;
    while((len = input_str[input_idx++])) {
#else
    while(scanf("%" SCNu16 ",", &len) == 1) {
#endif
        assert(len < ARR_SIZE && len >= 0);
        cur = reverse(arr, len, cur, skip_size++);
    }

#ifdef PART2
    for (int i = 0; i < sizeof(suffix); ++i) {
        cur = reverse(arr, suffix[i], cur, skip_size++);
    }

    } // closing for


    // dense hash calculation
    assert(ARR_SIZE % 16 == 0);
    uint8_t dense_hash[ARR_SIZE / 16];
    for (int i = 0; i < ARR_SIZE; i += 16) {
        uint8_t block = arr[i];
        for (int j = i + 1; j < i + 16; ++j) {
            block ^= arr[j];
        }
        dense_hash[i / 16] = block;
    }
#endif

#ifdef PART2
    for (int i = 0; i < sizeof(dense_hash); ++i) {
        printf("%02x", dense_hash[i]);
    }
    printf("\n");
#else
    printf("%d\n", (uint32_t)arr[0] * arr[1]);
#endif
}
