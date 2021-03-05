/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_die.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:25:02 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/05 19:10:22 by sbecker          ###   ########.fr       */
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
