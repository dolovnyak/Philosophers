/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:26:23 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/03 13:41:44 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			error(const char *error_str)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error_str, string_len(error_str));
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
}

static void	logging(const char *message, size_t philosopher_num,
		size_t time_start)
{
	size_t			time;
	struct timeval	timeval;
	char			str[255];
	size_t			len;

	ft_bzero(str, 100);
	gettimeofday(&timeval, NULL);
	time = get_current_time() - time_start;
	copy_size_t_to_string(str, time);
	len = numlen(time);
	ft_strcpy(str + len, "ms ");
	len += 3;
	copy_size_t_to_string(str + len, philosopher_num);
	len += numlen(philosopher_num);
	ft_strcpy(str + len, " ");
	++len;
	ft_strcpy(str + len, message);
	len += string_len(message);
	ft_strcpy(str + len, "\n");
	write(STDOUT_FILENO, str, string_len(str));
}

void		philosopher_log_die(t_philosopher *philosopher)
{
	logging("died", philosopher->number, philosopher->conf->start_time);
}

void		philosopher_log(t_philosopher *philosopher, const char *message)
{
	if (is_should_exit(philosopher))
		return ;
	logging(message, philosopher->number, philosopher->conf->start_time);
}
