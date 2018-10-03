#include "libc.h"

extern "C" void print_memory_nodes(void);

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
