/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:23:54 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/27 18:30:08 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (((long)time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_usleep(long msec, t_data *data)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < msec)
	{
		if (simulation_finished(data))
			break ;
		usleep(500);
	}
}
