#include "arena.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

bool is_power_of_two(uintptr_t x) { return (x & (x - 1)) == 0; }

uintptr_t align_forward(uintptr_t ptr, size_t align) {
    uintptr_t p, a, modulo;

    assert(is_power_of_two(align));

    p = ptr;
    a = (uintptr_t)align;

    modulo = p & (a - 1);

    if (modulo != 0) {
        p += a - modulo;
    }
    return p;
}
