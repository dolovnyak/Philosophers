#include "philosophers.h"

size_t	string_len(const char *s)
{
	size_t n;
	
	n = 0;
	while (s[n])
		n++;
	return (n);
}
