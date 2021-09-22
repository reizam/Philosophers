/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:38:41 by kmazier           #+#    #+#             */
/*   Updated: 2021/09/22 17:14:22 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_store	*create_store(t_settings *settings)
{
	t_store		*store;

	store = (t_store *)malloc(sizeof(t_store));
	if (!store)
		return (NULL);
	store->thread_clients = (pthread_t *)malloc(sizeof(pthread_t)
			* settings->number_of_philosophers);
	if (!store->thread_clients)
		return (free_store(store));
	store->keys = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* settings->number_of_philosophers);
	if (!store->keys)
		return (free_store(store));
	store->philos = NULL;
	store->one_dead = 0;
	store->settings = settings;
	return (store);
}

void	create_mutex(t_store **store, t_settings *settings)
{
	int	i;

	i = -1;
	while (++i < settings->number_of_philosophers)
	{
		if (pthread_mutex_init(&(*store)->keys[i], NULL))
			__exit_and_free("Philosophers: mutex error",
				EXIT_FAILURE, settings, (*store));
	}
	pthread_mutex_init(&(*store)->speak_lock, NULL);
}

t_philo	*get_philo_by_id(t_philo *philo, int index)
{
	while (philo)
	{
		if (index == philo->id)
			return (philo);
		philo = philo->next;
	}
	return (NULL);
}

void	start_threads(t_store **store, t_settings *settings)
{
	int	i;

	i = -1;
	while (++i < settings->number_of_philosophers)
		push(&(*store)->philos, i + 1, (*store));
	(*store)->start_time = get_current_ts();
	i = -1;
	while (++i < settings->number_of_philosophers)
	{
		if (pthread_create(&(*store)->thread_clients[i],
				NULL, philosopher_thread, get_philo_by_id((*store)->philos, i + 1)))
			__exit_and_free("Philosophers: thread error",
				EXIT_FAILURE, settings, (*store));
		usleep(1);
	}
}

void	start_philosophers(t_settings *settings)
{
	t_store	*store;
	int		i;

	if (!settings)
		__exit("Philosophers: malloc error\n", EXIT_FAILURE);
	store = create_store(settings);
	if (!store)
		__exit_and_free("Philosophers: malloc error\n",
			EXIT_FAILURE, settings, NULL);
	create_mutex(&store, settings);
	start_threads(&store, settings);
	pthread_create(&store->thread_manager, NULL,
		philo_manager_thread, &store);
	pthread_join(store->thread_manager, NULL);
	i = -1;
	while (++i < settings->number_of_philosophers)
		pthread_mutex_unlock(&store->keys[i]);
	i = -1;
	while (++i < settings->number_of_philosophers)
		pthread_join(store->thread_clients[i], NULL);
	i = -1;
	while (++i < settings->number_of_philosophers)
		pthread_mutex_destroy(&store->keys[i]);
	pthread_mutex_destroy(&store->speak_lock);
	__exit_and_free(NULL, EXIT_SUCCESS, settings, store);
}

int	main(int ac, char **av)
{
	if (ac < 5)
		__exit("Philosophers: too few arguments\n", EXIT_FAILURE);
	if (ac > 6)
		__exit("Philosophers: too many arguments\n", EXIT_FAILURE);
	if (!check_philo_args(av + 1))
		__exit("Philosophers: incorrect arguments\n", EXIT_FAILURE);
	start_philosophers(parse_philo_args(av + 1));
}
