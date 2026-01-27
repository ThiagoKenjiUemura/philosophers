/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:56:50 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/27 17:50:50 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_ms();
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				&routine, &data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Error: Invalid arguments\n"), 1);
	if (init_data(&data, argc, argv) || init_mutexes(&data)
		|| init_philos(&data))
		return (1);
	if (start_simulation(&data))
		return (1);
	monitor_check(&data);
	stop_simulation(&data);
	cleanup(&data);
	return (0);
}
