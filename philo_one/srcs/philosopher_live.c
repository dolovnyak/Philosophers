/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_live.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:59:21 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/03 13:40:36 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	take_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->first_fork);
	philosopher_log(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->second_fork);
	philosopher_log(philosopher, "has taken a fork");
}

static inline void	put_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(philosopher->second_fork);
	pthread_mutex_unlock(philosopher->first_fork);
}

static inline void	philosopher_eat(t_philosopher *philosopher,
		size_t *eat_times)
{
	take_forks(philosopher);
	++(*eat_times);
	pthread_mutex_lock(philosopher->last_time_eating_mutex);
	philosopher->last_time_eating = get_current_time();
	pthread_mutex_unlock(philosopher->last_time_eating_mutex);
	philosopher_log(philosopher, "is eating");
	ms_usleep(philosopher->conf->time_to_eat);
	put_forks(philosopher);
}

static inline int	is_eat_required_times(t_philosopher *philosopher,
		size_t eat_times)
{
	if (philosopher->conf->is_philosophers_must_eat_n_times == FALSE)
		return (FALSE);
	if (eat_times == philosopher->conf->philosopher_must_eat_times)
		return (TRUE);
	return (FALSE);
}

void				*philosopher_live(void *v_philosopher)
{
	t_philosopher	*philosopher;
	size_t			eat_times;

	eat_times = 0;
	philosopher = (t_philosopher *)v_philosopher;
	pthread_mutex_lock(philosopher->last_time_eating_mutex);
	philosopher->last_time_eating = get_current_time();
	pthread_mutex_unlock(philosopher->last_time_eating_mutex);
	while (TRUE)
	{
		if (is_should_exit(philosopher))
			return (NULL);
		philosopher_log(philosopher, "is thinking");
		philosopher_eat(philosopher, &eat_times);
		if (is_eat_required_times(philosopher, eat_times))
		{
			pthread_mutex_lock(philosopher->is_eaten_given_times_mutex);
			philosopher->is_eaten_given_times = TRUE;
			pthread_mutex_unlock(philosopher->is_eaten_given_times_mutex);
			return (NULL);
		}
		philosopher_log(philosopher, "is sleeping");
		ms_usleep(philosopher->conf->time_to_sleep);
	}
}
