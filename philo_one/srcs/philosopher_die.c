/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_die.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:25:02 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/09 05:25:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_die(t_philosopher *philosopher)
{
	if (*philosopher->exit == TRUE)
		return ;
	*philosopher->exit = TRUE;
    ms_usleep(5);
	log_philosopher_die(philosopher->conf->start_time, philosopher->number);
}

inline int	is_philosopher_die(t_philosopher *philosopher)
{
    if (get_current_time() - philosopher->last_time_eating >
        philosopher->conf->time_to_die)
        return (TRUE);
    return (FALSE);
}

inline int	is_philosopher_eat_n_times(t_philosopher *philosopher)
{
    if (philosopher->eating_n_times ==
        philosopher->conf->philosopher_must_eat_times)
        return (TRUE);
    return (FALSE);
}
