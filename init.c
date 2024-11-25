/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <abalasub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:01:42 by abalasub          #+#    #+#             */
/*   Updated: 2024/11/08 16:16:20 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	malloc_philo(char **argv, pthread_t **philosophers,
	pthread_mutex_t **forks, t_data **philo)
{
	*philosophers = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	if (!philosophers)
		return ;
	*forks = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	if (!forks)
	{
		free(philosophers);
		return ;
	}
	*philo = malloc(ft_atoi(argv[1]) * sizeof(t_data));
	if (!philo)
	{
		free(philosophers);
		free(forks);
		return ;
	}
}

void	init_forks(char **argv, pthread_mutex_t	*forks)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_chrono(char **argv, t_data *philo)
{
	struct timeval	tv;
	int				i;

	i = -1;
	gettimeofday(&tv, NULL);
	while (++i < ft_atoi(argv[1]))
		philo[i].start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	init_philo(char **argv, t_data *philo, pthread_mutex_t *forks
	, pthread_mutex_t printf_lock)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		philo[i].number_of_philosophers = ft_atoi(argv[1]);
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]) * 1000;
		philo[i].time_to_sleep = ft_atoi(argv[4]) * 1000;
		philo[i].last_meal = 0 ;
		philo[i].number_of_meal = 0;
		philo[i].enough_meal = 0;
		philo[i].i = i ;
		philo[i].forks = forks;
		philo[i].printf_lock = printf_lock;
		philo[i].alive = 1;
		philo[i].left = 0;
		philo[i].right = 0;
		philo[i].last_meal = 0;
		pthread_mutex_init(&philo[i].access_var, NULL);
	}
	init_chrono(argv, philo);
}

void	init_god(t_goddata *gdata, char **argv, t_data *philo)
{
	(*gdata).philo = philo;
	(*gdata).number_of_philo = ft_atoi(argv[1]);
	pthread_mutex_init(&gdata->printf_lock, NULL);
	if (!argv[5])
		(*gdata).meal_to_eat = -1;
	else
		(*gdata).meal_to_eat = ft_atoi(argv[5]);
	(*gdata).enough_eat = 0;
}
