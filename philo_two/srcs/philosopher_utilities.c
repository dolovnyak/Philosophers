/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_die.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:25:02 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/02 15:57:36 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline int	is_philosopher_die(t_philosopher *philosopher)
{
	sem_wait(philosopher->last_time_eating_semaphore);
	if (get_current_time() - philosopher->last_time_eating >
			philosopher->conf->time_to_die)
	{
		sem_post(philosopher->last_time_eating_semaphore);
		return (TRUE);
	}
	sem_post(philosopher->last_time_eating_semaphore);
	return (FALSE);
}

void		philosopher_die(t_philosopher *philosopher)
{
	sem_wait(philosopher->exit_semaphore);
	*(philosopher->exit) = TRUE;
	sem_post(philosopher->exit_semaphore);
	usleep(1000);
	philosopher_log_die(philosopher);
}

inline int	is_philosopher_eaten_required_times(t_philosopher *philosopher)
{
	sem_wait(philosopher->is_eaten_given_times_semaphore);
	if (philosopher->is_eaten_given_times == TRUE)
	{
		sem_post(philosopher->is_eaten_given_times_semaphore);
		return (TRUE);
	}
	sem_post(philosopher->is_eaten_given_times_semaphore);
	return (FALSE);
}

inline int	is_all_philosophers_eaten_required_times(
		t_philosopher *philosophers, size_t philosophers_num)
{
	size_t	i;

	i = -1;
	while (++i < philosophers_num)
		if (!is_philosopher_eaten_required_times(&(philosophers[i])))
			return (FALSE);
	return (TRUE);
}

inline int	is_should_exit(t_philosopher *philosopher)
{
	sem_wait(philosopher->exit_semaphore);
	if (*philosopher->exit == TRUE)
	{
		sem_post(philosopher->exit_semaphore);
		return (TRUE);
	}
	sem_post(philosopher->exit_semaphore);
	return (FALSE);
}
