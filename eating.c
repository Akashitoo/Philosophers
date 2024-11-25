/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <abalasub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:16:59 by abalasub          #+#    #+#             */
/*   Updated: 2024/11/14 15:10:38 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_my_fork(void *arg, pthread_mutex_t *forks, int number_of_philo)
{
	long int	time;
	int			number;

	pthread_mutex_lock(&((t_data *)arg)->access_var);
	time = ((t_data *)arg)->start;
	number = ((t_data *)arg)->i;
	pthread_mutex_unlock(&((t_data *)arg)->access_var);
	if ((number + 1) % number_of_philo == number % number_of_philo)
		return (0);
	pthread_mutex_lock(&forks[number % number_of_philo]);
	((t_data *)arg)->left = 1;
	pthread_mutex_lock(&((t_data *)arg)->access_var);
	if (!((t_data *)arg)->alive)
		return (0);
	pthread_mutex_unlock(&((t_data *)arg)->access_var);
	pthread_mutex_lock(&((t_data *)arg)->printf_lock);
	printf("\033[0;34m%ld %d has taken a fork\n",
		timestamp_in_ms(time), number + 1);
	pthread_mutex_unlock(&((t_data *)arg)->printf_lock);
	return (1);
}

int	take_his_fork(void *arg, pthread_mutex_t *forks, int number_of_philo)
{
	long int	time;
	int			number;

	pthread_mutex_lock(&((t_data *)arg)->access_var);
	time = ((t_data *)arg)->start;
	number = ((t_data *)arg)->i;
	pthread_mutex_unlock(&((t_data *)arg)->access_var);
	pthread_mutex_lock(&forks[(number + 1) % number_of_philo]);
	pthread_mutex_lock(&((t_data *)arg)->access_var);
	((t_data *)arg)->right = 1;
	if (!((t_data *)arg)->alive)
		return (0);
	pthread_mutex_unlock(&((t_data *)arg)->access_var);
	pthread_mutex_lock(&((t_data *)arg)->printf_lock);
	printf("\033[0;34m%ld %d has taken a fork\n",
		timestamp_in_ms(time), number + 1);
	pthread_mutex_unlock(&((t_data *)arg)->printf_lock);
	return (1);
}

int	how_take_forks(void *arg, pthread_mutex_t *forks, int number_of_philo)
{
	int	number;

	number = ((t_data *)arg)->i;
	if ((number + 1) % 2 == 0)
	{
		if (!take_my_fork(arg, forks, number_of_philo))
			return (0);
		if (!take_his_fork(arg, forks, number_of_philo))
			return (0);
	}
	else
	{
		usleep(500);
		if (!take_his_fork(arg, forks, number_of_philo))
			return (0);
		if (!take_my_fork(arg, forks, number_of_philo))
			return (0);
	}
	return (1);
}

void	how_to_put_down_forks(void *arg, pthread_mutex_t *forks
	, int number_of_philo)
{
	int	number;

	number = ((t_data *)arg)->i;
	if ((number + 1) % 2 == 0)
	{
		pthread_mutex_unlock(&forks[(number) % number_of_philo]);
		pthread_mutex_unlock(&forks[(number + 1) % number_of_philo]);
		((t_data *)arg)->left = 0;
		((t_data *)arg)->right = 0;
	}
	else
	{
		pthread_mutex_unlock(&forks[(number + 1) % number_of_philo]);
		pthread_mutex_unlock(&forks[(number) % number_of_philo]);
		((t_data *)arg)->left = 0;
		((t_data *)arg)->right = 0;
	}	
}

int	is_eating(void *arg, pthread_mutex_t *forks, int number_of_philo)
{
	long int	time;
	int			number;

	time = ((t_data *)arg)->start;
	number = ((t_data *)arg)->i;
	if (!how_take_forks(arg, forks, number_of_philo))
		return (0);
	pthread_mutex_lock(&((t_data *)arg)->printf_lock);
	printf("\033[0;32m%ld %d is eating\n", timestamp_in_ms(time), number + 1);
	pthread_mutex_unlock(&((t_data *)arg)->printf_lock);
	pthread_mutex_lock(&((t_data *)arg)->access_var);
	((t_data *)arg)->last_meal = timestamp_in_ms(time);
	((t_data *)arg)->number_of_meal += 1;
	pthread_mutex_unlock(&((t_data *)arg)->access_var);
	usleep(((t_data *)arg)->time_to_eat);
	how_to_put_down_forks(arg, forks, number_of_philo);
	pthread_mutex_lock(&((t_data *)arg)->access_var);
	if (!((t_data *)arg)->alive)
		return (0);
	pthread_mutex_unlock(&((t_data *)arg)->access_var);
	return (1);
}
