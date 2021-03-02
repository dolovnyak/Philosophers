/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:55:46 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/02 15:56:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	setup_semaphores(sem_t **forks_semaphore,
		sem_t **death_semaphore, t_conf *conf)
{
	sem_unlink("forks_semaphore");
	if ((*forks_semaphore = sem_open("forks_semaphore",
			O_CREAT | O_EXCL, S_IRWXU, conf->philosophers_num)) == SEM_FAILED)
		return (error("sem open"));
	sem_unlink("death_semaphore");
	if ((*death_semaphore = sem_open("death_semaphore",
			O_CREAT | O_EXCL, S_IRWXU, 1)) == SEM_FAILED)
		return (error("sem open"));
	return (SUCCESS);
}

int			setup_philosophers(t_philosopher **philosophers,
		t_conf *conf, int *exit)
{
	sem_t			*forks_semaphore;
	sem_t			*death_semaphore;
	size_t			i;

	if (!(*philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) *
			conf->philosophers_num)))
		return (error("philosophers malloc return NULL"));
	if (!(setup_semaphores(&forks_semaphore, &death_semaphore, conf)))
		return (error("setup semaphores"));
	i = -1;
	while (++i < conf->philosophers_num)
		(*philosophers)[i] = (t_philosopher){forks_semaphore, death_semaphore,
			i + 1, conf, 0, 0, FALSE, exit};
	return (SUCCESS);
}
