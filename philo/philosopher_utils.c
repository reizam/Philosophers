/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:19:43 by kmazier           #+#    #+#             */
/*   Updated: 2021/09/22 00:51:42 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_ts(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	get_philo_ts(t_philo *philo)
{
	return (get_current_ts() - philo->current_time);
}

void	philo_speak(t_philo *philo, char *msg, int force)
{
	int	current_time;

	if (!msg || (philo->store->one_dead && !force))
		return ;
	current_time = get_philo_ts(philo);
	pthread_mutex_lock(&philo->store->speak_lock);
	ft_putnbr_fd(current_time, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	ft_putnbr_fd(philo->id, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	write(STDOUT_FILENO, "\n", 1);
	pthread_mutex_unlock(&philo->store->speak_lock);
}

void	drop_forks(t_philo **philo)
{
	drop_left_fork(philo);
	drop_right_fork(philo);
}

void	*quit(t_philo **philo)
{
	drop_forks(philo);
	(*philo)->dead_time = -1;
	return (NULL);
}
