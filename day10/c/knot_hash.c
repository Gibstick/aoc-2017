#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

#define ARR_SIZE UINT8_MAX + 1

// reverse the order of len elements in the circular array
// starting at the current position
// and return the new position
uint8_t
reverse(uint8_t arr[const static ARR_SIZE], uint8_t len, uint8_t pos, uint8_t skip_size) {
    uint8_t lo = pos;
    uint8_t hi = pos + len - 1;
    for (int i = 0; i < len / 2; ++i) {
        uint8_t temp = arr[lo];
        arr[lo] = arr[hi];
        arr[hi] = temp;
        ++lo; --hi;
    }

    return pos + len + skip_size;
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
    uint8_t skip_size = 0;
    for (int i = 0; i < ARR_SIZE; ++i) {
        arr[i] = i;
    }

    uint16_t len;
    while(scanf("%" SCNu16 ",", &len) == 1) {
        assert(len < ARR_SIZE);
        cur = reverse(arr, len, cur, skip_size++);
    }
    printf("%d\n", (uint32_t)arr[0] * arr[1]);
}
