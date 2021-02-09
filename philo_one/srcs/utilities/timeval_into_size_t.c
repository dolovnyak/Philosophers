/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval_into_size_t.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:29:44 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/09 05:29:55 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline size_t	timeval_to_size_t(struct timeval timeval)
{
	return (timeval.tv_sec * 1000 + (size_t)(timeval.tv_usec * 0.001));
}
