#include "philosophers.h"

int fill_configuration_from_args(int argc, char **argv, t_configuration *configuration)
{
	int	i;
	
	if (argc < 5 || argc > 6)
		return (error("number of arguments is incorrect"));
	i = 0;
	while (argv[++i])
		if (!is_number(argv[i]))
			return (error("argument isn't number"));
	ft_bzero(configuration, sizeof(t_configuration));
	configuration->number_of_philosophers = string_to_int(argv[1]);
	configuration->time_to_die = string_to_int(argv[2]);
	configuration->time_to_eat = string_to_int(argv[3]);
	configuration->time_to_sleep = string_to_int(argv[4]);
	if (argc == 6)
	{
		configuration->number_of_times_each_philosopher_must_eat = string_to_int(argv[5]);
		if (configuration->number_of_times_each_philosopher_must_eat == 0)
			return (error("if you added 'eating number' argument, then at least value 1 needed"));
	}
	if (configuration->number_of_philosophers <= 1)
		return (error("at least two philosophers needed"));
	return (SUCCESS);
}
