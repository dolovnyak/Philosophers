/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:49:00 by sbecker           #+#    #+#             */
/*   Updated: 2021/02/28 09:07:04 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

# define SUCCESS 1
# define ERROR 0

# define TRUE 1
# define FALSE 0

typedef struct				s_configuration
{
	size_t					philosophers_num;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					number_each_philosopher_must_eat;
	size_t					start_time;
}							t_conf;

typedef struct				s_philosopher
{
	sem_t					*forks_semaphore;
	size_t					number;
	t_conf					*conf;
	size_t					*philosophers_who_eat_n_times;
	pthread_mutex_t			*increase_mutex;
	int						*exit;
}							t_philosopher;

size_t						string_len(const char *s);
int							is_number(char *str);
int							string_to_int(const char *str);
int							fill_configuration_from_args(int argc, char **argv,
		t_conf *conf);
int							error(const char *error_str);
void						*philosopher_live(void *v_philosopher);
void						log_philosopher(size_t time_start,
		size_t philosopher_num, const char *message, int exit_flag);
void						log_philosopher_die(size_t time_start,
		size_t philosopher_num);
size_t						timeval_to_size_t(struct timeval timeval);
size_t						get_current_time();
void						upgraded_usleep_in_ms(size_t sleep_time_in_ms);
void						*ft_memset(void *b, int c, size_t len);
void						ft_bzero(void *s, size_t n);
char						*ft_strcpy(char *dst, const char *src);
void						copy_size_t_to_string(char *string, size_t num);
size_t						numlen(int num);
void						philosopher_die(t_philosopher *philosopher);
void						clean_all(t_philosopher *philosophers);

#endif
