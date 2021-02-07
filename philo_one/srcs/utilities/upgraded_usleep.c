#include "philosophers.h"

void	upgraded_usleep(size_t sleep_time)
{
	struct timeval	start;
	struct timeval	step;
	
	gettimeofday(&start, NULL);
	while (TRUE)
	{
		usleep(10);
		gettimeofday(&step, NULL);
		if ((step.tv_sec - start.tv_sec) * 1000000 + (size_t)(step.tv_usec - start.tv_usec) >= sleep_time)
			return;
	}
}
