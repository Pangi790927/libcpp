#include "types.h"
#include "malloc.h"
#include <stdio.h>

const int MAX_SIZE = 1024 * 1024;
char heap[MAX_SIZE];
int current_size = 0;

extern "C" void *sbrk (intptr_t size) {
	if (current_size + size < 0)
		return (void *)-1;
	if (current_size + size >= MAX_SIZE)
		return (void *)-1;
	void *result = heap + current_size;
	current_size += size;
	return result;
}

extern "C" void print_memory_nodes() {
	malloc_head_t *node = (malloc_head_t *)heap;
	while (node && get_size(node)) {
		printf("[f:%d left: %5ld, right: %5ld, this: %5ld (size: %5ld)]\n", 
				(bool)(node->size & MALLOC_FREE_BIT),
				!node->next ? -1 : (char *)node->next - (char *)heap,
				!node->prev ? -1 : (char *)node->prev - (char *)heap,
				(char *)node - (char *)heap,
				get_size(node));
		node = get_right(node);
	}
}
