#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h> //TODO delete
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#define SUCCESS 1
#define ERROR 0

#define TRUE 1
#define FALSE 0

typedef struct				s_configuration
{
	size_t					number_of_philosophers;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					number_of_times_each_philosopher_must_eat;
	int						is_number_of_times_each_philosopher_must_eat_on;
	size_t					start_time;
	int						exit;
}							t_configuration;

typedef struct				s_fork
{
	pthread_mutex_t			mutex;
	size_t					number;
}							t_fork;

typedef struct				s_philosopher
{
	t_fork					*right_hand_fork;
	t_fork					*left_hand_fork;
	size_t					number;
	t_configuration			*configuration;
}							t_philosopher;

size_t						string_len(const char *s);
int							is_number(char *str);
int							string_to_int(const char *str);
int							fill_configuration_from_args(int argc, char **argv, t_configuration *configuration);
int							error(const char *error_str);
void						*philosopher_live(void *v_philosopher);
void 						log_philosopher(size_t time_start, size_t philosopher_num, const char *message);
size_t						timeval_to_size_t(struct timeval timeval);
size_t						get_current_time();
void						upgraded_usleep(size_t sleep_time);

#endif
