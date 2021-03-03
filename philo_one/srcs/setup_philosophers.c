/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:49:08 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/03 16:07:33 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	setup_mutexes(pthread_mutex_t **forks, t_conf *conf,
		pthread_mutex_t **exit_mutex)
{
	pthread_mutex_t	*tmp_forks;
	size_t			i;

	if (!(tmp_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
					* conf->philosophers_num)))
		return (error("new_forks malloc return NULL"));
	i = -1;
	while (++i < conf->philosophers_num)
		if (pthread_mutex_init(&(tmp_forks[i]), NULL))
			return (error("forks mutex init"));
	*forks = tmp_forks;
	if (!(*exit_mutex = (pthread_mutex_t *)malloc(
					sizeof(pthread_mutex_t))))
		return (error("exit mutex malloc return NULL"));
	if (pthread_mutex_init(*exit_mutex, NULL))
		return (error("exit mutex init"));
	return (SUCCESS);
}

int			setup_philosophers_own_mutexes(t_philosopher *philosophers,
		size_t philosophers_num)
{
	size_t			i;

	i = -1;
	while (++i < philosophers_num)
	{
		if (!(philosophers[i].is_eaten_given_times_mutex =
					(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
			return (error("eat malloc return NULL"));
		if (pthread_mutex_init(philosophers[i].is_eaten_given_times_mutex,
					NULL))
			return (error("eat mutex init"));
		if (!(philosophers[i].last_time_eating_mutex =
					(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
			return (error("eat malloc return NULL"));
		if (pthread_mutex_init(philosophers[i].last_time_eating_mutex, NULL))
			return (error("eat mutex init"));
	}
	return (SUCCESS);
}

int			setup_philosophers(t_philosopher **philosophers,
		t_conf *conf, int *exit)
{
	pthread_mutex_t	*exit_mutex;
	size_t			i;

	if (!(*philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
					* conf->philosophers_num)))
		return (error("philosophers malloc return NULL"));
	if (!(setup_mutexes(&conf->forks, conf, &exit_mutex)))
		return (error("setup forks"));
	i = -1;
	while (++i < conf->philosophers_num - 1)
		(*philosophers)[i] = (t_philosopher){conf, exit, i + 1,
			&(conf->forks[i]), &(conf->forks[i + 1]),
			exit_mutex, NULL, NULL, 0, 0};
	(*philosophers)[conf->philosophers_num - 1] =
		(t_philosopher){conf, exit, conf->philosophers_num,
			&(conf->forks[0]), &(conf->forks[conf->philosophers_num - 1]),
			exit_mutex, NULL, NULL, 0, 0};
	setup_philosophers_own_mutexes(*philosophers, conf->philosophers_num);
	return (SUCCESS);
}
