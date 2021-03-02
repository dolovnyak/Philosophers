/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_live.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:59:21 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/02 13:18:31 by sbecker          ###   ########.fr       */
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

static inline void	philosopher_eat(t_philosopher *philosopher)
{
	take_forks(philosopher);
	++(philosopher->eating_n_times);
	philosopher->last_time_eating = get_current_time();
	philosopher_log(philosopher, "is eating");
	ms_usleep(philosopher->conf->time_to_eat);
	put_forks(philosopher);
}

void				*philosopher_live(void *v_philosopher)
{
	t_philosopher	*philosopher;
	int				*exit;

	philosopher = (t_philosopher *)v_philosopher;
	exit = philosopher->exit;
	philosopher->last_time_eating = get_current_time();
	while (*exit == FALSE)
	{
		philosopher_log(philosopher, "is thinking");
		philosopher_eat(philosopher);
		philosopher_log(philosopher, "is sleeping");
		ms_usleep(philosopher->conf->time_to_sleep);
	}
	return (NULL);
}