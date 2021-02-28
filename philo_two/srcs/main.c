/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:04:56 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/28 05:24:47 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	setup_sem_mutex(sem_t **forks_semaphore, t_conf *conf,
                              pthread_mutex_t **increase_mutex)
{
	pthread_mutex_t	*tmp_increase_mutex;

    sem_unlink("forks_semaphore");
    if ((*forks_semaphore = sem_open("forks_semaphore", O_CREAT | O_EXCL, S_IRWXU, conf->philosophers_num)) == SEM_FAILED)
        return (error("sem open"));
	if (!(tmp_increase_mutex = (pthread_mutex_t *)malloc(
					sizeof(pthread_mutex_t))))
		return (error("increase mutex malloc return NULL"));
	if (pthread_mutex_init(tmp_increase_mutex, NULL))
		return (error("mutex init"));
	*increase_mutex = tmp_increase_mutex;
	return (SUCCESS);
}

static int	setup_philosophers(t_philosopher **philosophers, t_conf *conf,
		int *exit, size_t *philosophers_who_eat_n_times)
{
    sem_t           *forks_semaphore;
	pthread_mutex_t	*increase_mutex;
	size_t			i;

	if (!(*philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
					* conf->philosophers_num)))
		return (error("philosophers malloc return NULL"));
	if (!(setup_sem_mutex(&forks_semaphore, conf, &increase_mutex)))
		return (error("setup sem mutex"));
	i = -1;
	while (++i < conf->philosophers_num)
		(*philosophers)[i] = (t_philosopher){forks_semaphore,
			i + 1, conf, philosophers_who_eat_n_times, increase_mutex, exit};
	return (SUCCESS);
}

static int	launch_threads(t_philosopher *philosophers,
		t_conf *conf, pthread_t *threads)
{
	size_t	i;

	i = 0;
	conf->start_time = get_current_time();
	while (i < conf->philosophers_num)
	{
		if (pthread_create(&(threads[i]), NULL, philosopher_live,
					&(philosophers[i])))
			return (error("pthread create"));
		i += 2;
	}
	upgraded_usleep_in_ms(conf->time_to_eat);
	i = 1;
	while (i < conf->philosophers_num)
	{
		if (pthread_create(&(threads[i]), NULL, philosopher_live,
					&(philosophers[i])))
			return (error("pthread create"));
		i += 2;
	}
	return (SUCCESS);
}

static int	launch_philosophers_threads(t_philosopher *philosophers,
		t_conf *conf, int *exit, size_t *philosophers_who_eat_n_times)
{
	pthread_t	*threads;
	size_t		i;

	if (!(threads = (pthread_t *)malloc(sizeof(pthread_t) *
					conf->philosophers_num)))
		return (error("malloc threads"));
	if (!(launch_threads(philosophers, conf, threads)))
		return (error("launch threads"));
	if (conf->number_each_philosopher_must_eat != 0)
		while (*exit == FALSE)
			if (*philosophers_who_eat_n_times == conf->philosophers_num)
				*exit = TRUE;
	i = -1;
	while (++i < conf->philosophers_num)
		pthread_join(threads[i], NULL);
	free(threads);
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	t_conf			conf;
	t_philosopher	*philosophers;
	size_t			philosophers_who_eat_n_times;
	int				exit;

	if (!(fill_configuration_from_args(argc, argv, &conf)))
		return (error("invalid arguments"));
	exit = 0;
	philosophers_who_eat_n_times = 0;
	if (!(setup_philosophers(&philosophers, &conf, &exit,
					&philosophers_who_eat_n_times)))
		return (error("setup philosophers"));
	if (!(launch_philosophers_threads(philosophers, &conf, &exit,
					&philosophers_who_eat_n_times)))
		return (error("launch philosophers threads"));
	clean_all(philosophers);
	return (0);
}
