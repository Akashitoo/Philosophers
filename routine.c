/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <abalasub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:42:08 by abalasub          #+#    #+#             */
/*   Updated: 2024/11/08 16:17:36 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinking(void *arg, int number)
{
	long int	time;

	time = ((t_data *)arg)->start;
	pthread_mutex_lock(&((t_data *)arg)->access_var);
	if (!((t_data *)arg)->alive)
		return (0);
	pthread_mutex_unlock(&((t_data *)arg)->access_var);
	pthread_mutex_lock(&((t_data *)arg)->printf_lock);
	printf("\033[0;35m%ld %d is thinking\n", timestamp_in_ms(time), number + 1);
	pthread_mutex_unlock(&((t_data *)arg)->printf_lock);
	return (1);
}

int	is_sleeping(void *arg, long int time, int number)
{
	pthread_mutex_lock(&((t_data *)arg)->printf_lock);
	printf("\033[0;33m%ld %d is sleeping\n", timestamp_in_ms(time), number + 1);
	pthread_mutex_unlock(&((t_data *)arg)->printf_lock);
	usleep(((t_data *)arg)->time_to_sleep);
	pthread_mutex_lock(&((t_data *)arg)->access_var);
	if (!((t_data *)arg)->alive)
		return (0);
	pthread_mutex_unlock(&((t_data *)arg)->access_var);
	return (1);
}

void	*routine(void *arg)
{
	int				number;
	int				number_of_philo;
	pthread_mutex_t	*forks;
	long int		time;

	pthread_mutex_lock(&((t_data *)arg)->access_var);
	number = ((t_data *)arg)->i;
	number_of_philo = ((t_data *)arg)->number_of_philosophers;
	forks = ((t_data *)arg)->forks;
	time = ((t_data *)arg)->start;
	pthread_mutex_unlock(&((t_data *)arg)->access_var);
	while (((t_data *)arg)->alive)
	{
		if (!is_thinking(arg, number))
			break ;
		if (!is_eating(arg, forks, number_of_philo))
			break ;
		if (!is_sleeping(arg, time, number))
			break ;
	}
	if (((t_data *)arg)->left)
		pthread_mutex_unlock(&forks[number % number_of_philo]);
	if (((t_data *)arg)->right)
		pthread_mutex_unlock(&forks[(number + 1) % number_of_philo]);
	pthread_exit(NULL);
}
