/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:22:14 by kmazier           #+#    #+#             */
/*   Updated: 2021/09/24 16:42:47 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left_fork(t_philo **philo)
{
	int	left_id;

	left_id = (*philo)->id - 2;
	if (left_id < 0)
		left_id = (*philo)->store->settings->number_of_philosophers - 1;
	if ((*philo)->store->one_dead)
		return (0);
	pthread_mutex_lock(&(*philo)->store->keys[left_id]);
	philo_speak((*philo), "has taken a fork", 0);
	return (1);
}

int	take_right_fork(t_philo **philo)
{
	int	right_id;

	right_id = (*philo)->id - 1;
	if ((*philo)->store->one_dead)
		return (0);
	pthread_mutex_lock(&(*philo)->store->keys[right_id]);
	philo_speak((*philo), "has taken a fork", 0);
	return (1);
}

void	drop_left_fork(t_philo **philo)
{
	int	left_id;

	left_id = (*philo)->id - 2;
	if (left_id < 0)
		left_id = (*philo)->store->settings->number_of_philosophers - 1;
	pthread_mutex_unlock(&(*philo)->store->keys[left_id]);
}

void	drop_right_fork(t_philo **philo)
{
	int	right_id;

	right_id = (*philo)->id - 1;
	pthread_mutex_unlock(&(*philo)->store->keys[right_id]);
}

void	*philosopher_thread(void *p_data)
{
	t_philo	*philo;
	int		eat_left;

	philo = (t_philo *)p_data;
	eat_left
		= philo->store->settings->number_of_times_each_philosopher_must_eat;
	while (!philo->store->one_dead)
	{
		take_forks(&philo);
		if (!philo->store->one_dead)
			philo->dead_time = get_current_ts()
				+ philo->store->settings->time_to_die;
		philo_speak(philo, "is eating", 0);
		if (eat_left != -1 && --eat_left == 0)
			return (quit(&philo));
		_usleep(philo->store->settings->time_to_eat);
		drop_forks(&philo);
		philo_speak(philo, "is sleeping", 0);
		_usleep(philo->store->settings->time_to_sleep);
		philo_speak(philo, "is thinking", 0);
	}
	return (NULL);
}
