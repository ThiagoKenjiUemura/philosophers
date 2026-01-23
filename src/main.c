/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:56:50 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/23 17:12:13 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Number of arguments invalid.\n");
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
	{
		printf("Error: data inicialization failed. \n");
		return (1);
	}
	return (0);
}
