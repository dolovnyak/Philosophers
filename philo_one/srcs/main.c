#include "philosophers.h"
#include <stdio.h>

int setup_forks(t_fork **forks, t_configuration *configuration)
{
	t_fork	*tmp_forks;
	
	if (!(tmp_forks = (t_fork *)malloc(sizeof(t_fork) * configuration->number_of_philosophers)))
		return (error("new_forks malloc return NULL"));
	for (int i = 0; i < configuration->number_of_philosophers; i++)
	{
		if (pthread_mutex_init(&(tmp_forks[i].mutex), NULL))
			return (error("mutex init"));
		tmp_forks[i].number = i + 1;
	}
	
	*forks = tmp_forks;
	return (SUCCESS);
}

int setup_philosophers(t_philosopher **philosophers, t_configuration *configuration)
{
	t_fork	*forks;
	
	if (!(*philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * configuration->number_of_philosophers)))
		return (error("philosophers malloc return NULL"));
	if (!(setup_forks(&forks, configuration)))
		return (error("setup forks"));
	for (int i = 0; i < configuration->number_of_philosophers - 1; i++)
		(*philosophers)[i] = (t_philosopher){&(forks[i]), &(forks[i + 1]), i + 1, configuration};
	(*philosophers)[configuration->number_of_philosophers - 1] = (t_philosopher)
			{&(forks[configuration->number_of_philosophers - 1]), &(forks[0]), configuration->number_of_philosophers, configuration};
	
	return (SUCCESS);
}

int launch_philosophers_threads(t_philosopher *philosophers, const t_configuration *configuration)
{
	pthread_t *threads;
	
	if (!(threads = (pthread_t *)malloc(sizeof(pthread_t) * configuration->number_of_philosophers)))
		return (error("malloc threads"));
	for (int i = 0; i < configuration->number_of_philosophers; i++)
		if (pthread_create(&(threads[i]), NULL, philosopher_live, &(philosophers[i])))
			return (error("pthread create"));
	for (int i = 0; i < configuration->number_of_philosophers; i++)
		pthread_join(threads[i], NULL);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_configuration	configuration;
	t_philosopher	*philosophers = NULL;
	
	if (!(fill_configuration_from_args(argc, argv, &configuration)))
		return (error("invalid arguments"));
	
	configuration.start_time = get_current_time();
	configuration.exit = FALSE;
	
	if (!(setup_philosophers(&philosophers, &configuration)))
		return (error("setup philosophers"));
	
	if (!(launch_philosophers_threads(philosophers, &configuration)))
		return (error("launch philosophers threads"));
	
	return (0);
}
