/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:28:08 by kmazier           #+#    #+#             */
/*   Updated: 2021/09/22 00:17:57 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (!temp->store->one_dead && current_time >= temp->dead_time)
		{
			temp->store->one_dead = 1;
			philo_speak(temp, "died", 1);
			break ;
		}
		if (temp->next == NULL)
			temp = (*store)->philos;
		else
			temp = temp->next;
		_usleep(1);
	}
	return (NULL);
}
