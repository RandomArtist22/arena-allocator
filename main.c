#include "arena.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 1. Provide a backing buffer (1 MB on heap)
    size_t capacity = 1024 * 1024;
    void *buffer = malloc(capacity);

    // 2. Initialize the arena
    Arena arena;
    arena_init(&arena, buffer, capacity);

    // 3. Allocate memory (default 2 * sizeof(void*) alignment)
    int *numbers = arena_alloc(&arena, sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        numbers[i] = i * 2;
    }

    // 4. Custom alignment (SIMD / cache-line alignment of 64 bytes)
    float *matrix = arena_alloc_align(&arena, sizeof(float) * 16, 64);

    // 5. Resize an allocation (in-place if it was the last allocation)
    numbers =
        arena_resize(&arena, numbers, sizeof(int) * 100, sizeof(int) * 200);

    // 6. Free all allocations at once in O(1) time
    arena_free_all(&arena);

    // 7. Cleanup the raw backing buffer when finished with the arena
    free(buffer);
    return 0;
}
