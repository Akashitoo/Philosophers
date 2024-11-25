/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <abalasub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:26:44 by abalasub          #+#    #+#             */
/*   Updated: 2024/11/08 16:15:30 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_philo(char **argv, pthread_t *philosophers, t_data *philo
	, pthread_t god)
{
	int	i;
	int	value;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		value = pthread_create(&philosophers[i], NULL, &routine, &philo[i]);
		if (value != 0)
		{
			printf("FAIL MEMORY\n");
			kill_philos_error(philo, i);
			join_philo_error(philosophers, i, god);
			return (0);
		}
		i++;
	}
	return (1);
}

void	join_philo(char **argv, pthread_t *philosophers, pthread_t god)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
	pthread_join(god, NULL);
}

void	destroy_forks(char **argv, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	check_args(char **argv, int argc)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf("\033[0;31m Error: Not enough arguments\033[0;37m\n");
		printf("./philo nb_of_philo time_to_die time_do_eat time_to_sleep");
		printf(" [nb_of_meals] \n");
		return (0);
	}
	while (argv[i])
	{
		if (!is_number(argv[i]) || !is_int(argv[i]))
		{
			printf("\033[0;31m Error : Bad arguments\033[0;37m\n");
			printf(" All arguments must be positive integers !\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pthread_t		*philosophers;
	pthread_t		god;
	pthread_mutex_t	*forks;
	t_data			*philo;
	t_goddata		gdata;

	philosophers = NULL;
	forks = NULL;
	philo = NULL;
	if (!check_args(argv, argc))
		return (1);
	malloc_philo(argv, &philosophers, &forks, &philo);
	init_forks(argv, forks);
	init_god(&gdata, argv, philo);
	gdata.enough_eat = 0;
	init_philo(argv, philo, forks, gdata.printf_lock);
	pthread_create(&god, NULL, &godjob, &gdata);
	if (!launch_philo(argv, philosophers, philo, god))
		return (free_all(philo, philosophers, forks));
	join_philo(argv, philosophers, god);
	destroy_forks(argv, forks);
	free_all(philo, philosophers, forks);
}
