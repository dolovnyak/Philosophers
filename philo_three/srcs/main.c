/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 04:04:56 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/05 19:14:45 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	run_philosopher(t_philosopher *philosopher)
{
	pthread_t	philo_thread;

	philosopher->pid = fork();
	if (philosopher->pid == -1)
		return (error("fork error"));
	if (philosopher->pid != 0)
		return (SUCCESS);
	sem_wait(philosopher->start_semaphore);
	sem_post(philosopher->start_semaphore);
	philosopher->conf->start_time = get_current_time();
	if (philosopher->number % 2 == 0)
		philosopher->conf->time_to_eat < philosopher->conf->time_to_die ?
			ms_usleep(philosopher->conf->time_to_eat) :
			ms_usleep(philosopher->conf->time_to_die);
	if (pthread_create(&philo_thread, NULL, philosopher_live, philosopher))
		return (error("pthread create"));
	while (TRUE)
	{
		ms_usleep(1);
		if (is_philosopher_die(philosopher))
			exit(3);
		if (is_philosopher_eaten_required_times(philosopher))
			exit(4);
	}
}

static void	kill_philosophers(t_philosopher *philosophers,
		size_t philosophers_num)
{
	size_t	i;

	i = -1;
	while (++i < philosophers_num)
		kill(philosophers[i].pid, SIGKILL);
}

static void	monitor_philosophers(t_philosopher *philosophers, t_conf *conf)
{
	size_t	i;
	int		status;

	ms_usleep(2);
	i = -1;
	while (++i < conf->philosophers_num)
	{
		waitpid(philosophers[i].pid, &status, 0);
		if (WEXITSTATUS(status) == 3)
		{
			kill_philosophers(philosophers, conf->philosophers_num);
			return (philosopher_log_die(&(philosophers[i])));
		}
		if (i == 3 && WEXITSTATUS(status) == 4)
			return (kill_philosophers(philosophers, conf->philosophers_num));
	}
}

static int	launch_philosophers_processes(t_philosopher *philosophers,
		t_conf *conf)
{
	size_t i;

	i = -1;
	while (++i < conf->philosophers_num)
		if (!run_philosopher(&(philosophers[i])))
			return (error("run philosopher"));
	sem_post(philosophers[0].start_semaphore);
	conf->start_time = get_current_time();
	monitor_philosophers(philosophers, conf);
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	t_conf			conf;
	t_philosopher	*philosophers;

	if (!(fill_configuration_from_args(argc, argv, &conf)))
		return (error("invalid arguments"));
	if (!(setup_philosophers(&philosophers, &conf)))
		return (error("setup philosophers"));
	if (!(launch_philosophers_processes(philosophers, &conf)))
		return (error("launch philosophers processes"));
	clean_all(philosophers);
	exit(0);
}
