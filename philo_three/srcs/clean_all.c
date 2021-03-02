/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 05:18:01 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/02 13:18:50 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_philosopher *philosophers)
{
	sem_unlink("forks_semaphore");
	sem_close(philosophers[0].forks_semaphore);
	sem_unlink("death_semaphore");
	sem_close(philosophers[0].death_semaphore);
	free(philosophers);
}
