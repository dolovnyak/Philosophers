/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_live.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:59:21 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/09 05:27:31 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	take_forks(t_philosopher *philosopher)
{
    sem_wait(philosopher->forks_semaphore);
    log_philosopher(philosopher->conf->start_time, philosopher->number,
                    "has taken a fork", *philosopher->exit);
    sem_wait(philosopher->forks_semaphore);
	log_philosopher(philosopher->conf->start_time, philosopher->number,
					"has taken a fork", *philosopher->exit);
}

static inline void	put_forks(t_philosopher *philosopher)
{
    sem_post(philosopher->forks_semaphore);
    sem_post(philosopher->forks_semaphore);
}

static inline void	philosopher_sleep(t_philosopher *philosopher)
{
	log_philosopher(philosopher->conf->start_time, philosopher->number,
					"is sleeping", *philosopher->exit);
	upgraded_usleep_in_ms(philosopher->conf->time_to_sleep);
}

static inline int	eat(t_philosopher *philosopher,
		size_t *last_time_eating, size_t *eating_num)
{
	take_forks(philosopher);
	if (get_current_time() - *last_time_eating > philosopher->conf->time_to_die)
	{
		philosopher_die(philosopher);
		put_forks(philosopher);
		return (FALSE);
	}
	++(*eating_num);
	*last_time_eating = get_current_time();
	log_philosopher(philosopher->conf->start_time, philosopher->number,
					"is eating", *philosopher->exit);
	upgraded_usleep_in_ms(philosopher->conf->time_to_eat);
	put_forks(philosopher);
	if (*eating_num == philosopher->conf->number_each_philosopher_must_eat)
	{
		pthread_mutex_lock(philosopher->increase_mutex);
		++(*philosopher->philosophers_who_eat_n_times);
		pthread_mutex_unlock(philosopher->increase_mutex);
	}
	return (TRUE);
}

void				*philosopher_live(void *v_philosopher)
{
	t_philosopher	*philosopher;
	size_t			last_time_eating;
	size_t			eating_num;
	int				*exit;

	philosopher = (t_philosopher *)v_philosopher;
	eating_num = 0;
	exit = philosopher->exit;
	last_time_eating = get_current_time();
	while (*exit == FALSE)
	{
		if (get_current_time() - last_time_eating >
				philosopher->conf->time_to_die)
		{
			philosopher_die(philosopher);
			return (NULL);
		}
		log_philosopher(philosopher->conf->start_time, philosopher->number,
				"is thinking", *philosopher->exit);
		if (eat(philosopher, &last_time_eating, &eating_num) == FALSE)
			return (NULL);
		philosopher_sleep(philosopher);
	}
	return (NULL);
}
