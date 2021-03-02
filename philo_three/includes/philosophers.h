/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 05:49:00 by sbecker           #+#    #+#             */
/*   Updated: 2021/03/02 13:23:04 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

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
	size_t					philosopher_must_eat_times;
	size_t					start_time;
	int						is_philosophers_must_eat_n_times;
}							t_conf;

typedef struct				s_philosopher
{
	sem_t					*forks_semaphore;
	sem_t					*death_semaphore;
	size_t					number;
	t_conf					*conf;
	size_t					eating_n_times;
	size_t					last_time_eating;
	int						*exit;
	int						pid;
}							t_philosopher;

size_t						string_len(const char *s);
int							is_number(char *str);
int							string_to_int(const char *str);
int							fill_configuration_from_args(int argc, char **argv,
		t_conf *conf);
int							error(const char *error_str);
void						*philosopher_live(void *v_philosopher);
void						philosopher_log(t_philosopher *philosopher,
		const char *message);
void						log_philosopher_die(size_t time_start,
		size_t philosopher_num);
size_t						timeval_to_size_t(struct timeval timeval);
size_t						get_current_time();
void						ms_usleep(size_t sleep_time_in_ms);
void						*ft_memset(void *b, int c, size_t len);
void						ft_bzero(void *s, size_t n);
char						*ft_strcpy(char *dst, const char *src);
void						copy_size_t_to_string(char *string, size_t num);
size_t						numlen(int num);
void						philosopher_die(t_philosopher *philosopher);
void						philosopher_eat_n_times(
		t_philosopher *philosopher);
int							is_philosopher_die(t_philosopher *philosopher);
int							is_philosopher_eat_n_times(
		t_philosopher *philosopher);
void						clean_all(t_philosopher *philosophers);
int							setup_philosophers(t_philosopher **philosophers,
		t_conf *conf, int *exit);

#endif