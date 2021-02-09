/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:04:56 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/09 04:25:20 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	setup_forks(pthread_mutex_t **forks, t_conf *configuration)
{
	pthread_mutex_t	*tmp_forks;
	size_t			i;

	if (!(tmp_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
					* configuration->number_of_philosophers)))
		return (error("new_forks malloc return NULL"));
	i = -1;
	while (++i < configuration->number_of_philosophers)
		if (pthread_mutex_init(&(tmp_forks[i]), NULL))
			return (error("mutex init"));
	*forks = tmp_forks;
	return (SUCCESS);
}

int	setup_philosophers(t_philosopher **philosophers, t_conf *configuration,
		int *exit, size_t *philosophers_who_eat_n_times)
{
	pthread_mutex_t	*forks;
	size_t			i;

	if (!(*philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
					* configuration->number_of_philosophers)))
		return (error("philosophers malloc return NULL"));
	if (!(setup_forks(&forks, configuration)))
		return (error("setup forks"));
	i = -1;
	while (++i < configuration->number_of_philosophers - 1)
		(*philosophers)[i] = (t_philosopher){&(forks[i]), &(forks[i + 1]),
			i + 1, configuration, philosophers_who_eat_n_times, exit};
	(*philosophers)[configuration->number_of_philosophers - 1] =
		(t_philosopher){&(forks[0]),
		&(forks[configuration->number_of_philosophers - 1]),
		configuration->number_of_philosophers,
		configuration,
		philosophers_who_eat_n_times, exit};
	return (SUCCESS);
}

int	launch_threads(t_philosopher *philosophers,
		t_conf *configuration, pthread_t *threads)
{
	size_t	i;

	i = 0;
	configuration->start_time = get_current_time();
	while (i < configuration->number_of_philosophers)
	{
		if (pthread_create(&(threads[i]), NULL, philosopher_live,
					&(philosophers[i])))
			return (error("pthread create"));
		i += 2;
	}
	upgraded_usleep(configuration->time_to_eat);
	i = 1;
	while (i < configuration->number_of_philosophers)
	{
		if (pthread_create(&(threads[i]), NULL, philosopher_live,
					&(philosophers[i])))
			return (error("pthread create"));
		i += 2;
	}
	return (SUCCESS);
}

int	launch_philosophers_threads(t_philosopher *philosophers,
		t_conf *configuration, int *exit, size_t *philosophers_who_eat_n_times)
{
	pthread_t	*threads;
	size_t		i;

	if (!(threads = (pthread_t *)malloc(sizeof(pthread_t) *
					configuration->number_of_philosophers)))
		return (error("malloc threads"));
	if (!(launch_threads(philosophers, configuration, threads)))
		return (error("launch threads"));
	if (configuration->number_of_times_each_philosopher_must_eat != 0)
		while (*exit == FALSE)
			if (*philosophers_who_eat_n_times ==
					configuration->number_of_philosophers)
				*exit = TRUE;
	i = -1;
	while (++i < configuration->number_of_philosophers)
		pthread_join(threads[i], NULL);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_conf			configuration;
	t_philosopher	*philosophers;
	size_t			philosophers_who_eat_n_times;
	int				exit;

	if (!(fill_configuration_from_args(argc, argv, &configuration)))
		return (error("invalid arguments"));
	exit = 0;
	philosophers_who_eat_n_times = 0;
	if (!(setup_philosophers(&philosophers, &configuration, &exit,
					&philosophers_who_eat_n_times)))
		return (error("setup philosophers"));
	if (!(launch_philosophers_threads(philosophers, &configuration, &exit,
					&philosophers_who_eat_n_times)))
		return (error("launch philosophers threads"));
	return (0);
}
