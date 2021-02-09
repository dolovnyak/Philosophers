#include "philosophers.h"

inline size_t	numlen(int num)
{
	size_t	i;
	
	i = 1;
	if (num < 0)
		i++;
	while (num /= 10)
		i++;
	return (i);
}
