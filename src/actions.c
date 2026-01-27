/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:11:09 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/27 17:57:33 by thiagouemur      ###   ########.fr       */
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

static void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->fork_l]);
	print_action(philo, "has taken a fork");
	if (data->num_philos == 1)
	{
		usleep(data->time_to_die * 1000);
		pthread_mutex_unlock(&data->forks[philo->fork_l]);
		return ;
	}
	pthread_mutex_lock(&data->forks[philo->fork_r]);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[philo->fork_l]);
	pthread_mutex_unlock(&data->forks[philo->fork_r]);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_finished(philo->data))
	{
		philo_eat(philo);
		print_action(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_action(philo, "is thinking");
		usleep(500);
	}
	return (NULL);
}
