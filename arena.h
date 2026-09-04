#ifndef ARENA_H;
#define ARENA_H ;

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool is_power_of_two(uintptr_t x);
uintptr_t align_forward(uintptr_t ptr, size_t align);

#endif
