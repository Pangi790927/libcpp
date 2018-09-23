#include "libc.h"

void normal_delete(void* arg, unsigned long) {
	free(arg);
}