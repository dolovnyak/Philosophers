#include "philosophers.h"

size_t	get_current_time()
{
	struct timeval timeval;
	
	gettimeofday(&timeval, NULL);
	return (timeval_to_size_t(timeval));
}
