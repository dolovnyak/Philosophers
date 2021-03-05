/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 05:18:01 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/02 13:18:50 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_philosopher *philosophers)
{
	size_t	i;
	char	eat_times_name[sizeof(EAT_TIMES_SEM_NAME) + 1];
	char	last_eat_name[sizeof(LAST_EAT_SEM_NAME) + 1];

	ft_bzero(eat_times_name, sizeof(eat_times_name));
	ft_bzero(last_eat_name, sizeof(last_eat_name));
	ft_strcpy(eat_times_name, EAT_TIMES_SEM_NAME);
	ft_strcpy(last_eat_name, LAST_EAT_SEM_NAME);
	i = -1;
	while (++i < philosophers->conf->philosophers_num)
	{
		eat_times_name[sizeof(EAT_TIMES_SEM_NAME) - 1] = (char)('0' + (char)i);
		last_eat_name[sizeof(LAST_EAT_SEM_NAME) - 1] = (char)('0' + (char)i);
		sem_unlink(eat_times_name);
		sem_unlink(last_eat_name);
		sem_close(philosophers[i].is_eaten_given_times_semaphore);
		sem_close(philosophers[i].is_eaten_given_times_semaphore);
	}
	sem_unlink(FORKS_SEM_NAME);
	sem_close(philosophers[0].forks_semaphore);
	sem_unlink(START_SEM_NAME);
	sem_close(philosophers[0].start_semaphore);
	free(philosophers);
}
