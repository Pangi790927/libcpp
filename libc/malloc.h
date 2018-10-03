#ifndef MALLOC_H
#define MALLOC_H

extern "C" void *sbrk (intptr_t size);

#define MALLOC_FREE_BIT ((size_t)1 << (sizeof(size_t) * 8LL - 1LL))

// should we pack this one?
typedef struct malloc_head_s {
	size_t size;
	struct malloc_head_s *next;
	struct malloc_head_s *prev;
} malloc_head_t;

void			*malloc (size_t size);
void			free (void *ptr);
malloc_head_t*	get_right (malloc_head_t *node);
size_t			get_size (malloc_head_t *node);

#endif