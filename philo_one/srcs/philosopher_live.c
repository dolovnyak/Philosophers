#include "philosophers.h"

void	take_forks(t_philosopher *philosopher)
{
	log_philosopher(philosopher->configuration->start_time, philosopher->number, "has taken a fork");
	if (philosopher->number == philosopher->configuration->number_of_philosophers)
	{
		if (pthread_mutex_lock(&philosopher->left_hand_fork->mutex))
			error("left hand fork mutex lock");
		if (pthread_mutex_lock(&philosopher->right_hand_fork->mutex))
			error("right hand fork mutex lock");
	}
	else
	{
		if (pthread_mutex_lock(&philosopher->right_hand_fork->mutex))
			error("right hand fork mutex lock");
		if (pthread_mutex_lock(&philosopher->left_hand_fork->mutex))
			error("left hand fork mutex lock");
	}
}

void	put_forks(t_philosopher *philosopher)
{
	if (philosopher->number == philosopher->configuration->number_of_philosophers)
	{
		if (pthread_mutex_unlock(&philosopher->right_hand_fork->mutex))
			error("right hand fork mutex unlock");
		if (pthread_mutex_unlock(&philosopher->left_hand_fork->mutex))
			error("left hand fork mutex unlock");
	}
	else
	{
		if (pthread_mutex_unlock(&philosopher->left_hand_fork->mutex))
			error("left hand fork mutex unlock");
		if (pthread_mutex_unlock(&philosopher->right_hand_fork->mutex))
			error("right hand fork mutex unlock");
	}
}

void	eat(t_philosopher *philosopher)
{
	log_philosopher(philosopher->configuration->start_time, philosopher->number, "is eating");
	upgraded_usleep(philosopher->configuration->time_to_eat * 1000);
}

int		is_died_of_hunger(t_philosopher *philosopher, size_t last_time_eating)
{
	if (get_current_time() - last_time_eating > philosopher->configuration->time_to_die)
		return (TRUE);
	return (FALSE);
}

void	philosopher_die(t_philosopher *philosopher)
{
	log_philosopher(philosopher->configuration->start_time, philosopher->number, "died");
	philosopher->configuration->exit = TRUE;
}

void	philosopher_sleep(t_philosopher *philosopher)
{
	log_philosopher(philosopher->configuration->start_time, philosopher->number, "is sleeping");
	upgraded_usleep(philosopher->configuration->time_to_sleep * 1000);
}

void	*philosopher_live(void *v_philosopher)
{
	t_philosopher	*philosopher;
	size_t			last_time_eating;
	
	philosopher = (t_philosopher *)v_philosopher;
	last_time_eating = get_current_time();
	while (!philosopher->configuration->exit)
	{
		if (is_died_of_hunger(philosopher, last_time_eating))
		{
			philosopher_die(philosopher);
			return (NULL);
		}
		
		take_forks(philosopher);
		
		if (is_died_of_hunger(philosopher, last_time_eating))
		{
			philosopher_die(philosopher);
			put_forks(philosopher);
			return (NULL);
		}
		last_time_eating = get_current_time();
		eat(philosopher);
		put_forks(philosopher);
		philosopher_sleep(philosopher);
	}
	return (NULL);
}
