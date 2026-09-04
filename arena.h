#ifndef ARENA_H;
#define ARENA_H ;

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct Arena Arena;
struct Arena {
    unsigned char *buf;
    size_t buf_len;
    size_t prev_offset;
    size_t curr_offset;
};

#ifndef DEFUALT_ALIGNMENT
#define DEFUALT_ALIGNMENT (2 * sizeof(void *))
#endif

bool is_power_of_two(uintptr_t x);
uintptr_t align_forward(uintptr_t ptr, size_t align);
void *arena_alloc_align(Arena *a, size_t size, size_t align);
void *arena_alloc(Arena *a, size_t size);

#endif
