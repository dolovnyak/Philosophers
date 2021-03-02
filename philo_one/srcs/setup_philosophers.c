/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:49:08 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/02 16:52:35 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	setup_mutexes(pthread_mutex_t **forks, t_conf *conf,
		pthread_mutex_t **death_mutex)
{
	pthread_mutex_t	*tmp_forks;
	pthread_mutex_t	*tmp_death_mutex;
	size_t			i;

	if (!(tmp_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
					* conf->philosophers_num)))
		return (error("new_forks malloc return NULL"));
	i = -1;
	while (++i < conf->philosophers_num)
		if (pthread_mutex_init(&(tmp_forks[i]), NULL))
			return (error("mutex init"));
	*forks = tmp_forks;
	if (!(tmp_death_mutex = (pthread_mutex_t *)malloc(
					sizeof(pthread_mutex_t))))
		return (error("increase mutex malloc return NULL"));
	if (pthread_mutex_init(tmp_death_mutex, NULL))
		return (error("mutex init"));
	*death_mutex = tmp_death_mutex;
	return (SUCCESS);
}

int			setup_philosophers(t_philosopher **philosophers,
		t_conf *conf, int *exit)
{
	pthread_mutex_t	*death_mutex;
	size_t			i;

	if (!(*philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
					* conf->philosophers_num)))
		return (error("philosophers malloc return NULL"));
	if (!(setup_mutexes(&conf->forks, conf, &death_mutex)))
		return (error("setup forks"));
	i = -1;
	while (++i < conf->philosophers_num - 1)
		(*philosophers)[i] = (t_philosopher){&(conf->forks[i]),
			&(conf->forks[i + 1]), death_mutex,
			i + 1, conf, 0, 0, FALSE, exit};
	(*philosophers)[conf->philosophers_num - 1] =
		(t_philosopher){&(conf->forks[0]),
				&(conf->forks[conf->philosophers_num - 1]),
							death_mutex,
							conf->philosophers_num,
							conf, 0, 0, FALSE, exit};
	return (SUCCESS);
}
