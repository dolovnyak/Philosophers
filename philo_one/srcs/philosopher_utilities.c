/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_die.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:25:02 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/03 13:42:32 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		philosopher_die(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->exit_mutex);
	*philosopher->exit = TRUE;
	pthread_mutex_unlock(philosopher->exit_mutex);
	usleep(1000);
	philosopher_log_die(philosopher);
}

inline int	is_philosopher_die(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->last_time_eating_mutex);
	if (get_current_time() - philosopher->last_time_eating >
			philosopher->conf->time_to_die)
	{
		pthread_mutex_unlock(philosopher->last_time_eating_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(philosopher->last_time_eating_mutex);
	return (FALSE);
}

inline int	is_philosopher_eaten_required_times(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->is_eaten_given_times_mutex);
	if (philosopher->is_eaten_given_times == TRUE)
	{
		pthread_mutex_unlock(philosopher->is_eaten_given_times_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(philosopher->is_eaten_given_times_mutex);
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
	pthread_mutex_lock(philosopher->exit_mutex);
	if (*philosopher->exit == TRUE)
	{
		pthread_mutex_unlock(philosopher->exit_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(philosopher->exit_mutex);
	return (FALSE);
}
