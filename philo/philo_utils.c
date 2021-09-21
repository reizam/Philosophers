/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:25:07 by kmazier           #+#    #+#             */
/*   Updated: 2021/09/22 00:24:08 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_stack(int id, t_store *store)
{
	t_philo	*node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->id = id;
	node->right = 0;
	node->left = 0;
	node->current_time = get_current_ts();
	node->dead_time = node->current_time + store->settings->time_to_die;
	node->store = store;
	node->next = NULL;
	return (node);
}

void	push(t_philo **main_node, int id, t_store *store)
{
	t_philo	*node;

	node = new_stack(id, store);
	if (!node)
		return ;
	if (*main_node)
		node->next = *main_node;
	*main_node = node;
}

void	pop(t_philo **main_node)
{
	t_philo	*temp;

	if (*main_node == NULL)
		return ;
	temp = *main_node;
	*main_node = (*main_node)->next;
	free(temp);
}

void	_usleep(int time)
{
	int	current_ts;
	int	end;

	current_ts = get_current_ts();
	end = current_ts + time;
	while (current_ts < end)
		current_ts = get_current_ts();
}
