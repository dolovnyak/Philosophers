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

void	*philosopher_live(void *v_philosopher)
{
	t_philosopher	*philosopher;
	size_t			last_time_eating;
	
	philosopher = (t_philosopher *)v_philosopher;
	last_time_eating = get_current_time();
	while (1)
	{
		printf("delta time: %ld\n", get_current_time() - last_time_eating);
		printf("time to die %ld\n", philosopher->configuration->time_to_die);
		if (get_current_time() - last_time_eating > philosopher->configuration->time_to_die)
		{
			printf("philo %ld is died\n", philosopher->number);
			return NULL;
		}
		
		take_forks(philosopher);
		if (get_current_time() - last_time_eating > philosopher->configuration->time_to_die * 1000)
		{
			printf("philo %ld is died\n", philosopher->number);
			return NULL;
		}
		
		log_philosopher(philosopher->configuration->start_time, philosopher->number, "is eating");
		usleep(philosopher->configuration->time_to_eat * 1000);
		last_time_eating = get_current_time();
		
		put_forks(philosopher);
		
		log_philosopher(philosopher->configuration->start_time, philosopher->number, "is sleeping");
		usleep(philosopher->configuration->time_to_sleep * 1000);
	}
	return (NULL);
}
