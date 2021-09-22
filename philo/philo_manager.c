/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:28:08 by kmazier           #+#    #+#             */
/*   Updated: 2021/09/22 17:09:59 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_finished(t_philo *philo)
{
	if (philo->next != NULL)
		return (0);
	if (philo->store->settings->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	while (philo)
	{
		if (philo->dead_time != -1)
			return (0);
		philo = philo->next;
	}
	return (1);
}

void	*philo_manager_thread(void *p_data)
{
	t_store	**store;
	t_philo	*temp;
	int		current_time;

	store = (t_store **)p_data;
	temp = (*store)->philos;
	while (temp)
	{
		current_time = get_current_ts();
		if (!temp->store->one_dead && (current_time >= temp->dead_time)
			&& temp->dead_time != -1)
		{
			temp->store->one_dead = 1;
			philo_speak(temp, "died", 1);
			break ;
		}
		if (all_finished(temp))
			break ;
		if (!temp->next)
			temp = (*store)->philos;
		else
			temp = temp->next;
	}
	return (NULL);
}
