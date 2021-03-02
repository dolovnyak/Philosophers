/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:04:56 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/02 16:00:14 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	ms_usleep(conf->time_to_eat);
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

static void	monitor_philosophers(t_philosopher *philosophers, t_conf *conf)
{
	size_t	i;
	size_t	philosophers_who_eat_n_times;

	i = -1;
	philosophers_who_eat_n_times = 0;
	while (++i <= conf->philosophers_num)
	{
		if (i >= conf->philosophers_num)
		{
			i = 0;
			ms_usleep(5);
		}
		if (is_philosopher_die(&(philosophers[i])))
			return (philosopher_die(&(philosophers[i])));
		if (conf->is_philosophers_must_eat_n_times == TRUE)
			if (philosophers[i].is_eat_n_times == TRUE)
			{
				++philosophers_who_eat_n_times;
				if (philosophers_who_eat_n_times >= conf->philosophers_num)
					return ;
			}
	}
}

static int	launch_philosophers_threads(t_philosopher *philosophers,
		t_conf *conf)
{
	pthread_t	*threads;
	size_t		i;

	if (!(threads = (pthread_t *)malloc(sizeof(pthread_t) *
					conf->philosophers_num)))
		return (error("malloc threads"));
	if (!(launch_threads(philosophers, conf, threads)))
		return (error("launch threads"));
	ms_usleep(conf->time_to_eat);
	monitor_philosophers(philosophers, conf);
	i = -1;
	while (++i < conf->philosophers_num)
		pthread_detach(threads[i]);
	free(threads);
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	t_conf			conf;
	t_philosopher	*philosophers;
	int				exit;

	if (!(fill_configuration_from_args(argc, argv, &conf)))
		return (error("invalid arguments"));
	exit = 0;
	if (!(setup_philosophers(&philosophers, &conf, &exit)))
		return (error("setup philosophers"));
	if (!(launch_philosophers_threads(philosophers, &conf)))
		return (error("launch philosophers threads"));
	clean_all(philosophers);
	return (0);
}
