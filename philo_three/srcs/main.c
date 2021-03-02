/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:04:56 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/02 13:12:54 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	run_philosopher(t_philosopher *philosopher, t_conf *conf)
{
	pthread_t	philo_thread;

	philosopher->pid = fork();
	if (philosopher->pid == -1)
		return (error("fork error"));
	if (philosopher->pid != 0)
		return (SUCCESS);
	if (pthread_create(&philo_thread, NULL, philosopher_live, philosopher))
		return (error("pthread create"));
	pthread_detach(philo_thread);
	ms_usleep(conf->time_to_eat);
	while (TRUE)
	{
		ms_usleep(5);
		if (is_philosopher_die(philosopher))
			exit(3);
		if (conf->is_philosophers_must_eat_n_times == TRUE)
			if (is_philosopher_eat_n_times(philosopher))
			{
				*(philosopher->exit) = TRUE;
				ms_usleep(conf->time_to_eat + conf->time_to_sleep);
				exit(4);
			}
	}
}

static void	monitor_philosophers(t_philosopher *philosophers, t_conf *conf)
{
	size_t	i;
	size_t	philosophers_who_eat_n_times;
	int		status;

	philosophers_who_eat_n_times = 0;
	i = -1;
	while (++i < conf->philosophers_num)
	{
		waitpid(philosophers[i].pid, &status, 0);
		if (WEXITSTATUS(status) == 3)
		{
			philosopher_die(&(philosophers[i]));
			break ;
		}
		if (WEXITSTATUS(status) == 4)
		{
			++philosophers_who_eat_n_times;
			if (philosophers_who_eat_n_times == conf->philosophers_num)
				break ;
		}
		i = i == conf->philosophers_num ? -1 : i;
	}
	i = -1;
	while (++i < conf->philosophers_num)
		kill(philosophers[i].pid, SIGKILL);
}

static int	launch_philosophers_processes(t_philosopher *philosophers,
		t_conf *conf)
{
	size_t i;

	i = 0;
	conf->start_time = get_current_time();
	while (i < conf->philosophers_num)
	{
		if (!run_philosopher(&(philosophers[i]), conf))
			return (error("run philosopher"));
		i += 2;
	}
	ms_usleep(conf->time_to_eat);
	i = 1;
	while (i < conf->philosophers_num)
	{
		if (!run_philosopher(&(philosophers[i]), conf))
			return (error("run philosopher"));
		i += 2;
	}
	monitor_philosophers(philosophers, conf);
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	t_conf			conf;
	t_philosopher	*philosophers;
	int				exit_flag;

	if (!(fill_configuration_from_args(argc, argv, &conf)))
		return (error("invalid arguments"));
	exit_flag = 0;
	if (!(setup_philosophers(&philosophers, &conf, &exit_flag)))
		return (error("setup philosophers"));
	if (!(launch_philosophers_processes(philosophers, &conf)))
		return (error("launch philosophers processes"));
	clean_all(philosophers);
	exit(0);
}
