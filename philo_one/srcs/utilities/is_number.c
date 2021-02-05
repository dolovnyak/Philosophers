#include "philosophers.h"

int		is_number(char *str)
{
	if (!str || !*str)
		return (FALSE);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str++;
	}
	return (TRUE);
}
