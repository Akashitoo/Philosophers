/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <abalasub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:28:18 by abalasub          #+#    #+#             */
/*   Updated: 2024/11/08 16:27:09 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_think;
	int				time_to_sleep;
	int				alive;
	int				i;
	int				number_of_meal;
	int				enough_meal;
	int				left;
	int				right;
	long int		start;
	long int		last_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_lock;
	pthread_mutex_t	access_var;
}		t_data;

typedef struct s_goddata {
	t_data			*philo;
	int				number_of_philo;
	int				meal_to_eat;
	int				enough_eat;
	pthread_mutex_t	printf_lock;
}	t_goddata;

int			ft_atoi(const char *theString);
int			is_number(char *str);
int			is_int(char *str);
int			ft_strncmp(const char *first, const char *second, size_t length);
int			free_all(t_data *philo, pthread_t *philosophers,
				pthread_mutex_t *forks);
int			take_my_fork(void *arg, pthread_mutex_t *forks,
				int number_of_philo);
int			take_his_fork(void *arg, pthread_mutex_t *forks,
				int number_of_philo);
int			is_eating(void *arg, pthread_mutex_t *forks, int number_of_philo);
long int	timestamp_in_ms(long int start);
void		*routine(void *arg);
void		*godjob(void *arg);
void		malloc_philo(char **argv, pthread_t **philosophers,
				pthread_mutex_t **forks, t_data **philo);
void		init_forks(char **argv, pthread_mutex_t	*forks);
void		init_chrono(char **argv, t_data *philo);
void		init_god(t_goddata *gdata, char **argv, t_data *philo);
void		init_philo(char **argv, t_data *philo, pthread_mutex_t *forks,
				pthread_mutex_t printf_lock);
void		kill_philos_error(t_data *philo, int i);
void		join_philo_error(pthread_t *philosophers, int limit, pthread_t god);
#endif
