/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgraded_usleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:29:22 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/09 05:29:34 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline void	ms_usleep(size_t sleep_time_in_ms)
{
	struct timeval	start_time_tv;
	size_t			start_time;

	gettimeofday(&start_time_tv, NULL);
	start_time = timeval_to_size_t(start_time_tv);
	while (TRUE)
	{
		usleep(10);
		if (get_current_time() - start_time >= sleep_time_in_ms)
			return ;
	}
}
