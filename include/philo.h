/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:41:19 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/23 17:06:21 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int				meals_limit;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			fork_l;
	int			fork_r;
	t_data		*data;
}				t_philo;

int		main(int argc, char **argv);
int 	init_data(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);
int		init_philops(t_data *data);
//utils
long	ft_atoi_long(char *str);