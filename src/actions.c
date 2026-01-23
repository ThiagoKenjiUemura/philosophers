/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:11:09 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/23 18:22:30 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (!check_simulation_stop(philo->data))
		printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->write_lock);
}
