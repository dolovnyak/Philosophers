/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:04:56 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/03 13:35:23 by sbecker          ###   ########.fr       */
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

	i = -1;
	while (TRUE)
	{
		++i;
		if (i == conf->philosophers_num)
		{
			i = 0;
			ms_usleep(5);
		}
		if (is_all_philosophers_eaten_required_times(philosophers,
					conf->philosophers_num))
			return ;
		if (is_philosopher_eaten_required_times(&(philosophers[i])))
			continue;
		if (is_philosopher_die(&(philosophers[i])))
			return (philosopher_die(&(philosophers[i])));
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
		pthread_join(threads[i], NULL);
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
	clean_all(&conf, philosophers);
	return (0);
}
