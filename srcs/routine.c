/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:23:47 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 19:29:21 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	solo_death(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->death);
		if (*philo->dead == YES)
			break ;
		pthread_mutex_unlock(&philo->data->death);
	}
	pthread_mutex_unlock(&philo->data->death);
}

void	print_action(t_philo *philo, char *str)
{
	struct timeval	time;
	int				checker;

	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->death);
	if (*philo->dead == YES && *str != 'd')
	{
		pthread_mutex_unlock(&philo->data->death);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	gettimeofday(&time, NULL);
	pthread_mutex_unlock(&philo->data->death);
	checker = (time.tv_sec - philo->start.tv_sec) * 1000 \
	+ (time.tv_usec - philo->start.tv_usec) / 1000;
	printf("[%dms] %d %s\n", checker, philo->philo_id + 1, str);
	pthread_mutex_unlock(&philo->data->print);
}

void	eating(t_philo *philo)
{
	struct timeval	time;
	int				checker;

	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	if (philo->next)
	{
		pthread_mutex_lock(&philo->next->fork);
		print_action(philo, FORK);
		gettimeofday(&time, NULL);
		checker = time.tv_sec * 1000 + time.tv_usec / 1000;
		philo->last_meal = checker;
		print_action(philo, EAT);
		philo->meals++;
		my_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->next->fork);
	}
	else
		solo_death(philo);
	pthread_mutex_unlock(&philo->fork);
}

void	*routine(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	if (tmp->philo_id % 2)
		my_usleep(tmp->data->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&tmp->data->death);
		if (*tmp->dead == YES)
			break ;
		pthread_mutex_unlock(&tmp->data->death);
		eating(tmp);
		print_action(tmp, SLEEP);
		my_usleep(tmp->data->time_to_sleep);
		print_action(tmp, THINK);
	}
	pthread_mutex_unlock(&tmp->data->death);
	return (philo);
}
