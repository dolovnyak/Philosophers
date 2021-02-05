#include "philosophers.h"

int error(const char *error_str)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error_str, string_len(error_str));
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
}
