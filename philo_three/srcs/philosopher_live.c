/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_live.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:59:21 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/05 19:07:01 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	take_forks(t_philosopher *philosopher)
{
	sem_wait(philosopher->forks_semaphore);
	philosopher_log(philosopher, "has taken a fork");
	sem_wait(philosopher->forks_semaphore);
	philosopher_log(philosopher, "has taken a fork");
}

static inline void	put_forks(t_philosopher *philosopher)
{
	sem_post(philosopher->forks_semaphore);
	sem_post(philosopher->forks_semaphore);
}

static inline void	philosopher_eat(t_philosopher *philosopher,
		size_t *eat_times)
{
	take_forks(philosopher);
	++(*eat_times);
	sem_wait(philosopher->last_time_eating_semaphore);
	philosopher->last_time_eating = get_current_time();
	sem_post(philosopher->last_time_eating_semaphore);
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
	sem_wait(philosopher->last_time_eating_semaphore);
	philosopher->last_time_eating = get_current_time();
	sem_post(philosopher->last_time_eating_semaphore);
	while (TRUE)
	{
		philosopher_log(philosopher, "is thinking");
		philosopher_eat(philosopher, &eat_times);
		if (is_eat_required_times(philosopher, eat_times))
		{
			sem_wait(philosopher->is_eaten_given_times_semaphore);
			philosopher->is_eaten_given_times = TRUE;
			sem_post(philosopher->is_eaten_given_times_semaphore);
			return (NULL);
		}
		philosopher_log(philosopher, "is sleeping");
		ms_usleep(philosopher->conf->time_to_sleep);
	}
}
