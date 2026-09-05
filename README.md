# arena-allocator

This is a simple linear memory allocator written in C. Heavily inspired by [Ginger Bill's Memory Allocation Strategies Article Series](https://www.gingerbill.org/series/memory-allocation-strategies/).

I have made some minor improvements to the code including some bug fixes in the source code. Decided to make a repo since I am finding myself using this a lot.

### How to use

Add `arena.h` and `arena.c` into your project source and include the header:

```
#include "arena.h"
```

Basic example of usage from main.c

```
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
```
