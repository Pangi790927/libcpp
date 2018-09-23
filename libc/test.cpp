#include <stdio.h>
#include "libc.h"

const int MAX_SIZE = 1024 * 1024;
char buff[MAX_SIZE];
int current_size = 0;

void *sbrk (long long size) {
	if (current_size + size < 0)
		return (void *)-1;
	if (current_size + size >= MAX_SIZE)
		return (void *)-1;
	void *result = buff + current_size;
	current_size += size;
	return result;
}

void print_memory_nodes() {
	malloc_head_t *node = (malloc_head_t *)buff;
	while (node && get_size(node)) {
		printf("[f:%d left: %5ld, right: %5ld, this: %5ld (size: %5ld)]\n", 
				(bool)(node->size & MALLOC_FREE_BIT),
				!node->next ? -1 : (char *)node->next - (char *)buff,
				!node->prev ? -1 : (char *)node->prev - (char *)buff,
				(char *)node - (char *)buff,
				get_size(node));
		node = get_right(node);
	}
}

int main()
{
	/* Tests for all the components of libc*/

	/* malloc */
	malloc(1);
	malloc(2);
	malloc(3);
	malloc(4);
	print_memory_nodes();
		
	return 0;
}
