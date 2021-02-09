#include "philosophers.h"

inline void	upgraded_usleep(size_t sleep_time_in_ms)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	while (TRUE)
	{
		usleep(5);
		if (get_current_time() - timeval_to_size_t(start_time) >= sleep_time_in_ms)
			return ;
	}
}
