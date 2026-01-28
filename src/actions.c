/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:11:09 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/28 14:16:58 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->write_lock);
	pthread_mutex_lock(&philo->data->dead_lock);
	current_time = get_time_ms() - philo->data->start_time;
	if (philo->data->dead_flag == 0)
	{
		current_time = get_time_ms() - philo->data->start_time;
		printf("%ld %d %s\n", current_time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	simulation_finished(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->dead_lock);
	res = data->dead_flag;
	pthread_mutex_unlock(&data->dead_lock);
	return (res);
}

static void	update_meal_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
}

static void	philo_eat(t_philo *philo)
{
	int	f1;
	int	f2;

	f1 = philo->fork_l;
	f2 = philo->fork_r;
	if (f1 > f2)
	{
		f1 = philo->fork_r;
		f2 = philo->fork_l;
	}
	pthread_mutex_lock(&philo->data->forks[f1]);
	print_action(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		precise_usleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(&philo->data->forks[f1]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[f2]);
	print_action(philo, "has taken a fork");
	update_meal_status(philo);
	print_action(philo, "is eating");
	precise_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[f2]);
	pthread_mutex_unlock(&philo->data->forks[f1]);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_finished(philo->data))
	{
		philo_eat(philo);
		print_action(philo, "is sleeping");
		precise_usleep(data->time_to_sleep, data);
		print_action(philo, "is thinking");
		if (philo->data->num_philos % 2 != 0)
			precise_usleep(data->time_to_eat, data);
	}
	return (NULL);
}
