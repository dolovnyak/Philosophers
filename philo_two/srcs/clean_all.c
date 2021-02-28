/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 05:18:01 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/28 09:05:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_philosopher *philosophers)
{
	pthread_mutex_destroy(philosophers[0].increase_mutex);
	free(philosophers[0].increase_mutex);
	sem_unlink("forks_semaphore");
	sem_close(philosophers[0].forks_semaphore);
	free(philosophers);
}
