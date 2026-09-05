#include "arena.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t capacity = 1024 * 1024;
    void *buffer = malloc(capacity);

    Arena arena;
    arena_init(&arena, buffer, capacity);

    int *nums = arena_alloc(&arena, sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        nums[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    float f_num = 3.14f;

    printf("%f\n", f_num);

    arena_free(&arena, nums);
    arena_free(&arena, &f_num);

    arena_free_all(&arena);
    free(buffer);
    return 0;
}
