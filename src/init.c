/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:27:48 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/23 16:25:36 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	if(pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	while (i < data->num_philos)
	{
		if(pthread_mutex_init(&data->forks[i], NULL) != 0);
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long(argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
		data->meals_limit = ft_atoi_long(argv[5]);
	else
		data->meals_limit = -1;
	if (data->num_philos <= 0)
		return (1);
	if (init_mutexes(data) != 0)
		return (1);
	return (0); 
}
