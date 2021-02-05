#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <pthread.h>

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
}							t_configuration;

typedef struct				s_philosopher
{
	pthread_mutex_t			*left_hand_fork;
	pthread_mutex_t			*right_hand_fork;
	const t_configuration	*configuration;
}							t_philosopher;

size_t						string_len(const char *s);
int							is_number(char *str);
int							string_to_int(const char *str);
int							fill_configuration_from_args(int argc, char **argv, t_configuration *configuration);
int							error(const char *error_str);

#endif
