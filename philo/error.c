/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:29:40 by kmazier           #+#    #+#             */
/*   Updated: 2021/09/22 03:25:51 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__exit(char *msg, int exit_code)
{
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(exit_code);
}

t_store	*free_store(t_store *store)
{
	if (store->keys)
		free(store->keys);
	if (store->thread_clients)
		free(store->thread_clients);
	while (store->philos)
		pop(&store->philos);
	free(store);
	return (NULL);
}

void	__exit_and_free(char *msg, int exit_code,
		t_settings *settings, t_store *store)
{
	if (settings)
		free(settings);
	if (store)
		free_store(store);
	__exit(msg, exit_code);
}
