#include "libc.h"

// will need sbrk

static void 			init_malloc();
static void				*malloc_use_sbrk (size_t size);
static void				*malloc_use_node (malloc_head_t* to_use, size_t size);
static void				*malloc_insert_allocated (malloc_head_t *ptr,
									size_t size);
static void				malloc_remove_free (malloc_head_t *node);
static malloc_head_t	*malloc_push_free (malloc_head_t *node);
static malloc_head_t	*malloc_create_free (malloc_head_t *ptr, size_t size);
static size_t*			end_size (malloc_head_t *node);
static malloc_head_t*	get_left (malloc_head_t *node);
static void				malloc_concat_free_nodes (malloc_head_t *left,
									malloc_head_t *right);

static bool initialized = false;
static void *start_mem = NULL;
static void *end_mem = NULL;
static malloc_head_t *first_free = NULL;
static malloc_head_t *last_free = NULL;

static void init_malloc() {
	start_mem = end_mem = sbrk(0);
}

void *malloc (size_t size) {
	// not sure if malloc should return NULL if size == 0
	if (!initialized) {
		init_malloc();
		initialized = true;
	}
	if (size == 0)
		return NULL;
	if (size & MALLOC_FREE_BIT)
		return NULL;
	size = sizeof(malloc_head_t) + size + sizeof(size_t);
	if (!first_free) {
		return malloc_use_sbrk(size);
	}
	else {
		// get the first node we can use, maybe use an avl tree here
		malloc_head_t *to_use = NULL;
		for (malloc_head_t *current = first_free; current != NULL;
				current = current->next)
		{
			if (get_size(current) >= size) {
				to_use = current;
				break;
			}
		}

		if (!to_use) {
			return malloc_use_sbrk(size);
		}
		else {
			return malloc_use_node(to_use, size);
		}
	}
}

static void *malloc_use_sbrk (size_t size) {
	void *ret = sbrk(size);
	if (ret == (void *)-1)
		return NULL;
	// comment: if (ret != end_mem) error;
	// this means malloc must be given continuous space
	void *ret_val = malloc_insert_allocated((malloc_head_t *)ret, size);
	end_mem = (char *)end_mem + size;
	return ret_val;
}

static void *malloc_use_node (malloc_head_t* to_use, size_t size) {
	malloc_remove_free(to_use);
	if (get_size(to_use) < size + sizeof(malloc_head_t) + sizeof(size_t)) {
		// if we can't split the free node we use all of it
		return malloc_insert_allocated(to_use, get_size(to_use));
	}
	else {
		size_t total_size = get_size(to_use);
		void *res = malloc_insert_allocated(to_use, size);
		malloc_push_free(malloc_create_free(
				(malloc_head_t *)((char *)to_use + size),
				total_size - size));
		return res;
	}
}

static void *malloc_insert_allocated (malloc_head_t *ptr, size_t size) {
	ptr->size = size;
	*end_size(ptr) = size;
	return (char *)ptr + sizeof(size_t);
}

static malloc_head_t *malloc_create_free (malloc_head_t *ptr, size_t size) {
	ptr->size = size | MALLOC_FREE_BIT;
	ptr->next = NULL;
	ptr->prev = NULL;
	*end_size(ptr) = size;
	return ptr;
}

static malloc_head_t *malloc_push_free (malloc_head_t *node) {
	// at most one free node can be left of this node and 
	// at most one free node can be on the right
	if (get_left(node) && (get_left(node)->size & MALLOC_FREE_BIT)) {
		malloc_remove_free(get_left(node));
		node = get_left(node);
		malloc_concat_free_nodes(node, get_right(node));
		printf("concat l\n");
	}
	if (get_right(node) && (get_right(node)->size & MALLOC_FREE_BIT)) {
		malloc_remove_free(get_right(node));
		malloc_concat_free_nodes(node, get_right(node));
		printf("concat r\n");
	}
	node->prev = last_free;
	if (last_free) {
		last_free->next = node;
		last_free = node;
	}
	else
		last_free = first_free = node;
	return node;
}

static void malloc_remove_free (malloc_head_t *node) {
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;

	if (first_free == node)
		first_free = node->next;
	if (last_free == node)
		last_free = node->prev;
}

static malloc_head_t* get_left (malloc_head_t *node) {
	if (node == start_mem)
		return NULL;
	size_t left_size = *(size_t *)((char *)node - sizeof(size_t));
	return (malloc_head_t *)((char *)node - left_size);
}

malloc_head_t* get_right (malloc_head_t *node) {
	if ((char *)node + get_size(node) == end_mem)
		return NULL;
	return (malloc_head_t *)((char *)node + get_size(node));
}

static void malloc_concat_free_nodes (malloc_head_t *left,
		malloc_head_t *right)
{
	size_t new_size = get_size(left) + get_size(right);
	malloc_create_free(left, new_size);
}

static size_t *end_size (malloc_head_t *node) {
	return (size_t *)((char *)node + get_size(node)
			- sizeof(size_t));
}

size_t get_size (malloc_head_t *node) {
	return node->size & (~MALLOC_FREE_BIT);
}

void free (void *ptr) {
	if (ptr) {
		malloc_head_t *node = (malloc_head_t *)((char *)ptr - sizeof(size_t));
		node = malloc_push_free(malloc_create_free(node, get_size(node)));
		if (!get_right(node)) {
			malloc_remove_free(node);
			void *ret = sbrk(-get_size(node));
			if (ret != (void *)-1)
				end_mem = (char *)ret - get_size(node);
		}
	}
}
