/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:13:21 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/27 17:54:16 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->meal_lock);
	time = get_time_ms() - philo->last_meal;
	if (time >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static int	check_satiety(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->meals_limit == -1)
		return (0);
	i = 0;
	all_ate = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten >= data->meals_limit)
			all_ate++;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	return (all_ate == data->num_philos);
}

void	set_stop_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

void	monitor_check(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if (is_dead(&data->philos[i]))
			{
				print_action(&data->philos[i], "died");
				set_stop_flag(data);
				return ;
			}
		}
		if (check_satiety(data))
		{
			set_stop_flag(data);
			return ;
		}
		usleep(1000);
	}
}
