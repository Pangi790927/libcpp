#include "libc.h"

void	ft_normal_delete(void *ptr, size_t mem_size)
{
	free(ptr);
	(void)mem_size;
}
