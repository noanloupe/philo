/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:23:47 by noloupe           #+#    #+#             */
/*   Updated: 2023/07/10 19:02:32 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	solo_death(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex->death);
		if (*philo->dead == 1)
			break ;
		pthread_mutex_unlock(&philo->mutex->death);
	}
	pthread_mutex_unlock(&philo->mutex->death);
}

void	print_action(t_philo *philo, char *str)
{
	struct timeval	time;
	int				checker;

	pthread_mutex_lock(&philo->mutex->print);
	pthread_mutex_lock(&philo->mutex->death);
	if (*philo->dead == 1 && *str != 'd')
	{
		pthread_mutex_unlock(&philo->mutex->death);
		pthread_mutex_unlock(&philo->mutex->print);
		return ;
	}
	pthread_mutex_unlock(&philo->mutex->death);
	gettimeofday(&time, NULL);
	checker = (time.tv_sec - philo->start.tv_sec) * 1000 \
	+ time.tv_usec / 1000 - philo->start.tv_usec / 1000;
	printf("[%d ms] %d %s\n", checker, philo->philo_id + 1, str);
	pthread_mutex_unlock(&philo->mutex->print);
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
		++philo->meals;
		my_usleep(philo->data->time_to_eat, philo);
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
		my_usleep(tmp->data->time_to_eat / 2, tmp);
	while (1)
	{
		pthread_mutex_lock(&tmp->mutex->death);
		if (*tmp->dead)
			break ;
		pthread_mutex_unlock(&tmp->mutex->death);
		eating(tmp);
		print_action(tmp, SLEEP);
		my_usleep(tmp->data->time_to_sleep, tmp);
		print_action(tmp, THINK);
	}
	pthread_mutex_unlock(&tmp->mutex->death);
	return (NULL);
}
