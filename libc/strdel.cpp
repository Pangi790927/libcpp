#include "libc.h"

void	strdel(char **as)
{
	if (as != NULL)
	{
		if (*as != NULL)
		{
			free((void *)(*as));
			*as = NULL;
		}
	}
}
