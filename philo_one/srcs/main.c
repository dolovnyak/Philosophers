#include "philosophers.h"
#include <stdio.h>

int setup_forks(pthread_mutex_t **forks, t_configuration *configuration)
{
	pthread_mutex_t	*tmp_forks;
	
	if (!(tmp_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * configuration->number_of_philosophers)))
		return (error("new_forks malloc return NULL"));
	for (size_t i = 0; i < configuration->number_of_philosophers; i++)
		if (pthread_mutex_init(&(tmp_forks[i]), NULL))
			return (error("mutex init"));
	
	*forks = tmp_forks;
	return (SUCCESS);
}

int setup_philosophers(t_philosopher **philosophers, t_configuration *configuration, int *exit, size_t *philosophers_who_eat_n_times)
{
	pthread_mutex_t	*forks;
	
	if (!(*philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * configuration->number_of_philosophers)))
		return (error("philosophers malloc return NULL"));
	if (!(setup_forks(&forks, configuration)))
		return (error("setup forks"));
	for (size_t i = 0; i < configuration->number_of_philosophers - 1; i++)
		(*philosophers)[i] = (t_philosopher){&(forks[i]), &(forks[i + 1]), i + 1, configuration, philosophers_who_eat_n_times, exit};
	
	(*philosophers)[configuration->number_of_philosophers - 1] =
			(t_philosopher){&(forks[0]),&(forks[configuration->number_of_philosophers - 1]), configuration->number_of_philosophers, configuration, philosophers_who_eat_n_times, exit};
	
	return (SUCCESS);
}

int launch_philosophers_threads(t_philosopher *philosophers, t_configuration *configuration, int *exit, size_t *philosophers_who_eat_n_times)
{
	pthread_t	*threads;
	
	if (!(threads = (pthread_t *)malloc(sizeof(pthread_t) * configuration->number_of_philosophers)))
		return (error("malloc threads"));
	configuration->start_time = get_current_time();
	for (size_t i = 0; i < configuration->number_of_philosophers; i+=2)
		if (pthread_create(&(threads[i]), NULL, philosopher_live, &(philosophers[i])))
			return (error("pthread create"));
	upgraded_usleep(configuration->time_to_eat);
	for (size_t i = 1; i < configuration->number_of_philosophers; i+=2)
		if (pthread_create(&(threads[i]), NULL, philosopher_live, &(philosophers[i])))
			return (error("pthread create"));
		
	if (configuration->number_of_times_each_philosopher_must_eat != 0)
		while (*exit == FALSE)
			if (*philosophers_who_eat_n_times == configuration->number_of_philosophers)
				*exit = TRUE;
		
	for (size_t i = 0; i < configuration->number_of_philosophers; i++)
		pthread_join(threads[i], NULL);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_configuration	configuration;
	t_philosopher	*philosophers = NULL;
	size_t			philosophers_who_eat_n_times;
	int				exit;
	
	if (!(fill_configuration_from_args(argc, argv, &configuration)))
		return (error("invalid arguments"));
	exit = 0;
	philosophers_who_eat_n_times = 0;
	if (!(setup_philosophers(&philosophers, &configuration, &exit, &philosophers_who_eat_n_times)))
		return (error("setup philosophers"));
	if (!(launch_philosophers_threads(philosophers, &configuration, &exit, &philosophers_who_eat_n_times)))
		return (error("launch philosophers threads"));
	return (0);
}
