#include "philosophers.h"

void	copy_size_t_to_string(char *string, size_t num)
{
	size_t			len;
	
	len = numlen(num);
	if (string == NULL)
		return ;
	string[--len] = num % 10 + '0';
	while (num /= 10)
		string[--len] = num % 10 + '0';
}
