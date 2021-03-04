/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:55:46 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/04 17:03:35 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	setup_semaphores(sem_t **forks_semaphore,
		sem_t **exit_semaphore, t_conf *conf)
{
	sem_unlink(FORKS_SEM_NAME);
	if ((*forks_semaphore = sem_open(FORKS_SEM_NAME,
			O_CREAT | O_EXCL, 0777, conf->philosophers_num)) == SEM_FAILED)
		return (error("sem open"));
	sem_unlink(EXIT_SEM_NAME);
	if ((*exit_semaphore = sem_open(EXIT_SEM_NAME,
			O_CREAT | O_EXCL, 0777, 1)) == SEM_FAILED)
		return (error("sem open"));
	return (SUCCESS);
}

static int	setup_philosophers_own_semaphores(t_philosopher *philosophers,
		size_t philosophers_num)
{
	size_t	i;
	char	eat_times_name[sizeof(EAT_TIMES_SEM_NAME) + 1];
	char	last_eat_name[sizeof(LAST_EAT_SEM_NAME) + 1];

	ft_bzero(eat_times_name, sizeof(eat_times_name));
	ft_bzero(last_eat_name, sizeof(last_eat_name));
	ft_strcpy(eat_times_name, EAT_TIMES_SEM_NAME);
	ft_strcpy(last_eat_name, LAST_EAT_SEM_NAME);
	i = -1;
	while (++i < philosophers_num)
	{
		eat_times_name[sizeof(EAT_TIMES_SEM_NAME) - 1] = (char)('0' + (char)i);
		last_eat_name[sizeof(LAST_EAT_SEM_NAME) - 1] = (char)('0' + (char)i);
		sem_unlink(eat_times_name);
		sem_unlink(last_eat_name);
		if (!(philosophers[i].is_eaten_given_times_semaphore = sem_open(
				eat_times_name, O_CREAT | O_EXCL, 0777, 1)))
			return (error("sem open"));
		if (!(philosophers[i].last_time_eating_semaphore = sem_open(
				last_eat_name, O_CREAT | O_EXCL, 0777, 1)))
			return (error("sem open"));
	}
	return (SUCCESS);
}

int			setup_philosophers(t_philosopher **philosophers,
		t_conf *conf, int *exit)
{
	sem_t			*forks_semaphore;
	sem_t			*exit_semaphore;
	size_t			i;

	if (!(*philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) *
			conf->philosophers_num)))
		return (error("philosophers malloc return NULL"));
	if (!(setup_semaphores(&forks_semaphore, &exit_semaphore, conf)))
		return (error("setup semaphores"));
	i = -1;
	while (++i < conf->philosophers_num)
		(*philosophers)[i] = (t_philosopher){conf, exit, i + 1,
			forks_semaphore, exit_semaphore, NULL, NULL,
			get_current_time(), FALSE};
	setup_philosophers_own_semaphores(*philosophers, conf->philosophers_num);
	return (SUCCESS);
}
