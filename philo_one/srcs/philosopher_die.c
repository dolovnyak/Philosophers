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
	upgraded_usleep_in_ms(5);
	log_philosopher_die(philosopher->conf->start_time, philosopher->number);
}
