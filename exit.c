/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <abalasub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:13:24 by abalasub          #+#    #+#             */
/*   Updated: 2024/11/08 16:14:13 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philos_error(t_data *philo, int i)
{
	int	nb;

	nb = 0;
	while (nb < i + 1)
	{
		pthread_mutex_lock(&philo[nb].access_var);
		if (philo[nb].alive != 0)
			philo[nb].alive = 0;
		pthread_mutex_unlock(&philo[nb].access_var);
		nb++;
	}
}

void	join_philo_error(pthread_t *philosophers, int limit, pthread_t god)
{
	int	i;

	i = 0;
	pthread_join(god, NULL);
	while (i < limit)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
}

int	free_all(t_data *philo, pthread_t *philosophers, pthread_mutex_t *forks)
{
	free(philo);
	free(philosophers);
	free(forks);
	return (0);
}
