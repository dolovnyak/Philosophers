/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_configuration_from_args.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:28:23 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/28 05:16:28 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fill_configuration_from_args(int argc, char **argv, t_conf *conf)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (error("number of arguments is incorrect"));
	i = 0;
	while (argv[++i])
		if (!is_number(argv[i]))
			return (error("argument isn't number"));
	ft_bzero(conf, sizeof(t_conf));
	conf->philosophers_num = string_to_int(argv[1]);
	conf->time_to_die = string_to_int(argv[2]);
	conf->time_to_eat = string_to_int(argv[3]);
	conf->time_to_sleep = string_to_int(argv[4]);
	if (argc == 6)
	{
		conf->number_each_philosopher_must_eat =
			string_to_int(argv[5]);
		if (conf->number_each_philosopher_must_eat == 0)
			return (error("for 'eating number' at least value 1 needed"));
	}
	if (conf->philosophers_num <= 1)
		return (error("at least two philosophers needed"));
	return (SUCCESS);
}
