/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <abalasub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:37:22 by abalasub          #+#    #+#             */
/*   Updated: 2024/11/08 15:53:41 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_last_meal(t_data *philo, int nb)
{
	pthread_mutex_lock(&philo[nb].printf_lock);
	pthread_mutex_lock(&philo[nb].access_var);
	if (timestamp_in_ms(philo[nb].start)
		- philo[nb].last_meal > philo[nb].time_to_die)
	{
		printf("\033[0;31m%ld %d died\n",
			timestamp_in_ms(philo[nb].start), philo[nb].i + 1);
		philo[nb].alive = 0;
		pthread_mutex_unlock(&philo[nb].access_var);
		return (0);
	}
	pthread_mutex_unlock(&philo[nb].printf_lock);
	return (1);
}

void	check_enough_eat(void *arg, t_data *philo, int nb)
{
	if (!philo[nb].enough_meal
		&& philo[nb].number_of_meal == ((t_goddata *)arg)->meal_to_eat)
	{	
		((t_goddata *)arg)->enough_eat += 1;
		philo[nb].enough_meal = 1;
	}
}

void	kill_philos(void *arg, t_data *philo)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (nb + 1 < ((t_goddata *)arg)->number_of_philo)
	{
		nb = i % ((t_goddata *)arg)->number_of_philo;
		pthread_mutex_lock(&philo[nb].access_var);
		if (philo[nb].alive != 0)
			philo[nb].alive = 0;
		pthread_mutex_unlock(&philo[nb].access_var);
		i++;
	}
}

void	*godjob(void *arg)
{
	t_data	*philo;
	int		i;
	int		nb;

	philo = ((t_goddata *)arg)->philo;
	i = 0;
	while ((((t_goddata *)arg)->meal_to_eat == -1)
		|| (((t_goddata *)arg)->meal_to_eat > -1
			&& ((t_goddata *)arg)->enough_eat
			!= ((t_goddata *)arg)->number_of_philo))
	{
		nb = i % ((t_goddata *)arg)->number_of_philo;
		if (!check_last_meal(philo, nb))
			break ;
		check_enough_eat(arg, philo, nb);
		pthread_mutex_unlock(&philo[nb].access_var);
		i++;
	}
	kill_philos(arg, philo);
	pthread_exit(NULL);
}
