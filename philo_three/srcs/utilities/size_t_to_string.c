/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_t_to_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:28:36 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/09 05:28:42 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	copy_size_t_to_string(char *string, size_t num)
{
	size_t			len;

	len = numlen(num);
	if (string == NULL)
		return ;
	string[--len] = num % 10 + '0';
	while (num /= 10)
		string[--len] = num % 10 + '0';
}
