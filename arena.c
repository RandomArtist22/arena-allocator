#include "arena.h"
#include <assert.h>
#include <stddef.h>
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

void *arena_alloc_align(Arena *a, size_t size, size_t align) {
    uintptr_t curr_ptr = (uintptr_t)a->buf + (uintptr_t)a->curr_offset;
    uintptr_t offset = align_forward(curr_ptr, align);
    offset -= (uintptr_t)a->buf;

    if (offset + size <= a->buf_len) {
        void *ptr = &a->buf[offset];
        a->prev_offset = offset;
        a->curr_offset = offset + size;

        memset(ptr, 0, size);
        return ptr;
    }
    return NULL;
}

void *arena_alloc(Arena *a, size_t size) {
    arena_alloc_align(a, size, DEFUALT_ALIGNMENT);
}
