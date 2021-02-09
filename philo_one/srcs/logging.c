/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:26:23 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/09 04:27:23 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		error(const char *error_str)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error_str, string_len(error_str));
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
}

void	log_philosopher_die(size_t time_start, size_t philosopher_num)
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
	ft_strcpy(str + len, "died");
	len += string_len("died");
	ft_strcpy(str + len, "\n");
	write(STDOUT_FILENO, str, string_len(str));
}

void	log_philosopher(size_t time_start, size_t philosopher_num,
		const char *message, int exit_flag)
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
	if (exit_flag == TRUE)
		return ;
	write(STDOUT_FILENO, str, string_len(str));
}
