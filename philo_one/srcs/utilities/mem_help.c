#include "philosophers.h"

inline void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*a;
	
	a = b;
	i = 0;
	while (i < len)
	{
		a[i] = (char)c;
		i++;
	}
	return (b);
}

inline void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
