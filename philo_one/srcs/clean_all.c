/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 05:18:01 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/28 05:22:38 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_conf *conf, t_philosopher *philosophers)
{
	size_t	i;

	i = -1;
	while (++i < conf->philosophers_num)
		pthread_mutex_destroy(&(conf->forks[i]));
	free(conf->forks);
	pthread_mutex_destroy(philosophers[0].death_mutex);
	free(philosophers[0].death_mutex);
	free(philosophers);
}
