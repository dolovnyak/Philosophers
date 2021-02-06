#include "philosophers.h"
#include <stdio.h>

int		error(const char *error_str)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error_str, string_len(error_str));
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
}

void	print_str(const char *str)
{
	write(STDOUT_FILENO, str, string_len(str));
	write(STDERR_FILENO, "\n", 1);
}

void	log_philosopher(size_t time_start, size_t philosopher_num, const char *message)
{
	size_t			time;
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	time = get_current_time() - time_start;
	printf("%ldms %ld %s\n", time, philosopher_num, message);
}
