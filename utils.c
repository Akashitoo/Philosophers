/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <abalasub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:38:48 by abalasub          #+#    #+#             */
/*   Updated: 2024/11/08 16:08:42 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *theString)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	i = 0;
	sign = 1;
	while (theString[i] == ' '
		|| (theString[i] >= '\t' && theString[i] <= '\r'))
		i++;
	if (theString[i] == '-' || theString[i] == '+')
	{
		if (theString[i] == '-')
			sign *= -1;
		i++;
	}
	while (theString[i] >= '0' && theString[i] <= '9')
	{
		res = res * 10 + (theString[i] - 48);
		i++;
	}
	return (res * sign);
}

long int	timestamp_in_ms(long int start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start);
}

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	int	i;

	if (!length)
		return (length);
	i = 0;
	while (first[i] && second[i] && first[i] == second[i] && length - 1)
	{
		i++;
		length--;
	}
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	is_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 10)
		return (0);
	if (i == 10 && ft_strncmp("2147483647", str, 10) < 0)
		return (0);
	return (1);
}
