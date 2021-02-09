#include "philosophers.h"

static inline void	take_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->first_fork);
	log_philosopher(philosopher->configuration->start_time, philosopher->number, "has taken a fork", *philosopher->exit);
	pthread_mutex_lock(philosopher->second_fork);
	log_philosopher(philosopher->configuration->start_time, philosopher->number, "has taken a fork", *philosopher->exit);
}

static inline void	put_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(philosopher->second_fork);
	pthread_mutex_unlock(philosopher->first_fork);
}

static inline void	eat(t_philosopher *philosopher)
{
	log_philosopher(philosopher->configuration->start_time, philosopher->number, "is eating", *philosopher->exit);
	upgraded_usleep(philosopher->configuration->time_to_eat);
}

void	philosopher_die(t_philosopher *philosopher)
{
	if (*philosopher->exit == TRUE)
		return;
	*philosopher->exit = TRUE;
	upgraded_usleep(1);
	log_philosopher_die(philosopher->configuration->start_time, philosopher->number);
}

void	philosopher_sleep(t_philosopher *philosopher)
{
	log_philosopher(philosopher->configuration->start_time, philosopher->number, "is sleeping", *philosopher->exit);
	upgraded_usleep(philosopher->configuration->time_to_sleep);
}

void	*philosopher_live(void *v_philosopher)
{
	t_philosopher	*philosopher;
	size_t			last_time_eating;
	int				*exit;
	int				eating_num;
	int				must_eat_num;
	
	philosopher = (t_philosopher *)v_philosopher;
	eating_num = 0;
	must_eat_num = philosopher->configuration->number_of_times_each_philosopher_must_eat;
	exit = philosopher->exit;
	last_time_eating = get_current_time();
	while (*exit == FALSE)
	{
		if (get_current_time() - last_time_eating > philosopher->configuration->time_to_die)
		{
			philosopher_die(philosopher);
			return (NULL);
		}
		
		take_forks(philosopher);
		
		if (get_current_time() - last_time_eating > philosopher->configuration->time_to_die)
		{
			philosopher_die(philosopher);
			put_forks(philosopher);
			return (NULL);
		}
		eating_num++;
		last_time_eating = get_current_time();
		eat(philosopher);
		put_forks(philosopher);
		if (eating_num == must_eat_num)
			++(*philosopher->philosophers_who_eat_n_times);
		
		philosopher_sleep(philosopher);
	}
	return (NULL);
}
