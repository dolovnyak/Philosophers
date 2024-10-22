/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:28:27 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/09 05:28:30 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline size_t	numlen(size_t num)
{
	size_t	i;

	i = 1;
	if (num < 0)
		i++;
	while (num /= 10)
		i++;
	return (i);
}
