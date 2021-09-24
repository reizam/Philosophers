/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:39:10 by kmazier           #+#    #+#             */
/*   Updated: 2021/09/24 16:51:47 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef struct s_settings
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_settings;

typedef struct s_store
{
	pthread_t		*thread_clients;
	pthread_t		thread_manager;
	t_settings		*settings;
	pthread_mutex_t	*keys;
	pthread_mutex_t	speak_lock;
	struct s_philo	*philos;
	int				start_time;
	int				one_dead;
}	t_store;

typedef struct s_philo
{
	t_store			*store;
	int				id;
	int				left;
	int				right;
	int				dead_time;
	struct s_philo	*next;
}	t_philo;

size_t			ft_strlen(const char *s);
int				ft_is_number(char *str);
long long int	ft_atoi(char *str);
int				check_philo_args(char **args);
t_settings		*parse_philo_args(char **args);
void			__exit(char *msg, int exit_code);
void			__exit_and_free(char *msg, int exit_code,
					t_settings *settings, t_store *store);
void			*philosopher_thread(void *p_data);
t_philo			*new_stack(int id, t_store *store);
void			push(t_philo **main_node, int id, t_store *store);
void			pop(t_philo **main_node);
int				get_current_ts(void);
int				get_philo_ts(t_philo *philo);
void			*philo_manager_thread(void *p_data);
void			_usleep(int time);
void			ft_putnbr_fd(int n, int fd);
void			philo_speak(t_philo *philo, char *msg, int force);
t_store			*free_store(t_store *store);
void			drop_right_fork(t_philo **philo);
void			drop_left_fork(t_philo **philo);
void			drop_forks(t_philo **philo);
void			take_forks(t_philo **philo);
void			*quit(t_philo **philo);
t_philo			*get_philo_by_id(t_philo *philo, int index);
int				take_right_fork(t_philo **philo);
int				take_left_fork(t_philo **philo);

#endif