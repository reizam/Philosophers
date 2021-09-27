/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:47:24 by kmazier           #+#    #+#             */
/*   Updated: 2021/09/27 04:05:25 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_args(char **args)
{
	int				i;
	long long int	temp;

	i = -1;
	while (args && args[++i])
	{
		if (!ft_is_number(args[i]))
			return (0);
		temp = ft_atoi(args[i]);
		if (temp < 1 || temp >= INT_MAX)
			return (0);
	}
	return (1);
}

void	set_settings(int id, int value, t_settings **settings)
{
	if (id == 0)
		(*settings)->number_of_philosophers = value;
	else if (id == 1)
		(*settings)->time_to_die = value;
	else if (id == 2)
		(*settings)->time_to_eat = value;
	else if (id == 3)
		(*settings)->time_to_sleep = value;
	else if (id == 4)
		(*settings)->number_of_times_each_philosopher_must_eat = value;
}

t_settings	*parse_philo_args(char **args)
{
	t_settings	*settings;
	int			i;

	settings = (t_settings *)malloc(sizeof(t_settings));
	if (!settings)
		return (NULL);
	i = -1;
	set_settings(4, -1, &settings);
	while (args[++i])
		set_settings(i, (int)ft_atoi(args[i]), &settings);
	return (settings);
}
