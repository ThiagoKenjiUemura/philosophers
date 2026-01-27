/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:41:19 by thiagouemur       #+#    #+#             */
/*   Updated: 2026/01/27 17:54:25 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_limit;
	long			start_time;
	int				dead_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				fork_l;
	int				fork_r;
	t_data			*data;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	meal_lock;
}				t_philo;

int		main(int argc, char **argv);
int		init_data(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);
int		init_philos(t_data *data);
long	get_time_ms(void);
void	print_action(t_philo *philo, char *msg);
void	*routine(void *arg);
void	monitor_check(t_data *data);
void	set_stop_flag(t_data *data);
//utils
long	ft_atoi_long(char *str);
void	cleanup(t_data *data);

#endif