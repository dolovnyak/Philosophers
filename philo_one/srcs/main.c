#include "philosophers.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_configuration	configuration;
	
	if (!(fill_configuration_from_args(argc, argv, &configuration)))
		return (error("invalid arguments"));
	
	printf("np: %ld\n", configuration.number_of_philosophers);
	printf("np: %ld\n", configuration.time_to_die);
	printf("np: %ld\n", configuration.time_to_eat);
	printf("np: %ld\n", configuration.time_to_sleep);
	printf("np: %ld\n", configuration.number_of_times_each_philosopher_must_eat);
	printf("np: %d\n", configuration.is_number_of_times_each_philosopher_must_eat_on);
	
	return (0);
}
