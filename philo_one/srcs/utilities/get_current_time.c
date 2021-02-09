#include "philosophers.h"

inline size_t	get_current_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval_to_size_t(timeval));
}
